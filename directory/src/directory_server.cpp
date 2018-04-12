#include <iostream>
#include <vector>
#include <thread>
#include <directory/fs/directory_tree.h>
#include <directory/block/random_block_allocator.h>
#include <directory/fs/directory_server.h>
#include <directory/lease/lease_expiry_worker.h>
#include <directory/lease/lease_server.h>
#include <storage/manager/storage_manager.h>
#include <utils/signal_handling.h>
#include <utils/cmd_parse.h>
#include <directory/block/block_allocation_server.h>
#include <utils/logger.h>
#include <directory/block/file_size_tracker.h>

using namespace ::elasticmem::directory;
using namespace ::elasticmem::storage;
using namespace ::elasticmem::utils;

using namespace ::apache::thrift;

int main(int argc, char **argv) {
  signal_handling::install_error_handler(SIGABRT, SIGFPE, SIGSEGV, SIGILL, SIGTRAP);

  GlobalOutput.setOutputFunction(log_utils::log_thrift_msg);

  cmd_options opts;
  opts.add(cmd_option("address", 'a', false).set_default("0.0.0.0").set_description("Address server binds to"));
  opts.add(cmd_option("service-port", 's', false).set_default("9090").set_description(
      "Port that directory service listens on"));
  opts.add(cmd_option("lease-port", 'l', false).set_default("9091").set_description(
      "Port that lease service listens on"));
  opts.add(cmd_option("block-port", 'b', false).set_default("9092").set_description(
      "Port that block advertisement service listens on"));
  opts.add(cmd_option("lease-period-ms", 'p', false).set_default("10000").set_description(
      "Lease duration (in ms) that lease service advertises"));
  opts.add(cmd_option("grace-period-ms", 'g', false).set_default("10000").set_description(
      "Grace period (in ms) that lease service waits for beyond lease duration"));
  opts.add(cmd_option("storage-trace-file", 't', false).set_required(false).set_description(
      "Trace file for logging storage capacity over time"));

  cmd_parser parser(argc, argv, opts);
  if (parser.get_flag("help")) {
    std::cout << parser.help_msg() << std::endl;
    return 0;
  }

  std::string address;
  int service_port;
  int lease_port;
  int block_port;
  uint64_t lease_period_ms;
  uint64_t grace_period_ms;
  std::string storage_trace;

  try {
    address = parser.get("address");
    service_port = parser.get_int("service-port");
    lease_port = parser.get_int("lease-port");
    block_port = parser.get_int("block-port");
    lease_period_ms = static_cast<uint64_t>(parser.get_long("lease-period-ms"));
    grace_period_ms = static_cast<uint64_t>(parser.get_long("grace-period-ms"));
    storage_trace = parser.get("storage-trace-file");
  } catch (cmd_parse_exception &ex) {
    std::cerr << "Could not parse command line args: " << ex.what() << std::endl;
    std::cerr << parser.help_msg() << std::endl;
    return -1;
  }

  std::mutex failure_mtx;
  std::condition_variable failure_condition;
  std::atomic<int> failing_thread(-1); // alloc -> 0, directory -> 1, lease -> 2

  std::exception_ptr alloc_exception = nullptr;
  auto alloc = std::make_shared<random_block_allocator>();
  auto alloc_server = block_allocation_server::create(alloc, address, block_port);
  std::thread alloc_serve_thread([&alloc_exception, &alloc_server, &failing_thread, &failure_condition] {
    try {
      alloc_server->serve();
    } catch (...) {
      alloc_exception = std::current_exception();
      failing_thread = 0;
      failure_condition.notify_all();
    }
  });
  LOG(log_level::info) << "Block allocation server listening on " << address << ":" << block_port;

  std::exception_ptr directory_exception = nullptr;
  auto storage = std::make_shared<storage_manager>();
  auto tree = std::make_shared<directory_tree>(alloc, storage);
  auto directory_server = directory_server::create(tree, address, service_port);
  std::thread directory_serve_thread([&directory_exception, &directory_server, &failing_thread, &failure_condition] {
    try {
      directory_server->serve();
    } catch (...) {
      directory_exception = std::current_exception();
      failing_thread = 1;
      failure_condition.notify_all();
    }
  });

  LOG(log_level::info) << "Directory server listening on " << address << ":" << service_port;

  std::exception_ptr lease_exception = nullptr;
  auto lease_server = lease_server::create(tree, lease_period_ms, address, lease_port);
  std::thread lease_serve_thread([&lease_exception, &lease_server, &failing_thread, &failure_condition] {
    try {
      lease_server->serve();
    } catch (...) {
      lease_exception = std::current_exception();
      failing_thread = 2;
      failure_condition.notify_all();
    }
  });

  LOG(log_level::info) << "Lease server listening on " << address << ":" << lease_port;

  lease_expiry_worker lmgr(tree, lease_period_ms, grace_period_ms);
  lmgr.start();

  file_size_tracker tracker(tree, storage, lease_period_ms, storage_trace);
  if (!storage_trace.empty()) {
    tracker.start();
  }

  std::unique_lock<std::mutex> failure_condition_lock{failure_mtx};
  failure_condition.wait(failure_condition_lock, [&failing_thread] {
    return failing_thread != -1;
  });

  switch (failing_thread.load()) {
    case 0:
      if (alloc_exception) {
        try {
          std::rethrow_exception(alloc_exception);
        } catch (std::exception &e) {
          LOG(log_level::error) << "Block allocation server failed: " << e.what();
        }
      }
      break;
    case 1:
      if (directory_exception) {
        try {
          std::rethrow_exception(directory_exception);
        } catch (std::exception &e) {
          LOG(log_level::error) << "Directory server failed: " << e.what();
        }
      }
      break;
    case 2:
      if (lease_exception) {
        try {
          std::rethrow_exception(lease_exception);
        } catch (std::exception &e) {
          LOG(log_level::error) << "Lease server failed: " << e.what();
          std::exit(-1);
        }
      }
      break;
    default:break;
  }
  return -1;
}
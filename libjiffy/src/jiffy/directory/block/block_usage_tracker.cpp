#include "block_usage_tracker.h"
#include "../../utils/logger.h"
#include "../../utils/directory_utils.h"
#include <utility>
#include <iostream>

namespace jiffy {
namespace directory {

using namespace utils;

block_usage_tracker::block_usage_tracker(std::shared_ptr<block_allocator> alloc,
                                     uint64_t periodicity_ms,
                                     const std::string &output_file)
    : periodicity_ms_(periodicity_ms),
      output_file_(output_file),
      alloc_(std::move(alloc)) {}

block_usage_tracker::~block_usage_tracker() {
  stop_.store(true);
  if (worker_.joinable())
    worker_.join();
}

void block_usage_tracker::start() {
  worker_ = std::thread([&] {
    std::ofstream out(output_file_);
    while (!stop_.load()) {
      auto start = std::chrono::steady_clock::now();
      try {
        report_allocated_blocks(out);
      } catch (std::exception &e) {
        LOG(error) << "Exception: " << e.what();
      }
      auto end = std::chrono::steady_clock::now();
      auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

      auto time_to_wait = std::chrono::duration_cast<std::chrono::milliseconds>(periodicity_ms_ - elapsed);
      if (time_to_wait > std::chrono::milliseconds::zero()) {
        std::this_thread::sleep_for(time_to_wait);
      }
    }
    out.close();
  });
}

void block_usage_tracker::stop() {
  stop_.store(true);
}

void block_usage_tracker::report_allocated_blocks(std::ofstream &out) {
  auto timestamp = jiffy::utils::time_utils::now_ms();
  out << timestamp << ",\t" << alloc_->num_allocated_blocks() << std::endl;
}

}
}

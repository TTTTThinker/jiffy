#include "catch.hpp"
#include "../src/directory/fs/directory_tree.h"
#include "../src/directory/block/random_block_allocator.h"
#include "test_utils.h"

using namespace ::elasticmem::directory;
using namespace ::elasticmem::utils;

TEST_CASE("create_directory_test", "[dir]") {
  auto alloc = std::make_shared<dummy_block_allocator>(4);
  auto sm = std::make_shared<dummy_storage_manager>();
  directory_tree tree(alloc, sm);

  REQUIRE_NOTHROW(tree.create_directories("/sandbox/1/2/a"));
  REQUIRE(tree.is_directory("/sandbox/1/2/a"));
  REQUIRE(tree.is_directory("/sandbox/1/2"));
  REQUIRE(tree.is_directory("/sandbox/1"));
  REQUIRE(tree.is_directory("/sandbox"));

  REQUIRE_NOTHROW(tree.create_directory("/sandbox/1/2/b"));
  REQUIRE(tree.is_directory("/sandbox/1/2/b"));

  REQUIRE_THROWS_AS(tree.create_directory("/sandbox/1/1/b"), directory_ops_exception);
}

TEST_CASE("create_file_test", "[file][dir]") {
  auto alloc = std::make_shared<dummy_block_allocator>(4);
  auto sm = std::make_shared<dummy_storage_manager>();
  directory_tree tree(alloc, sm);

  REQUIRE_NOTHROW(tree.create("/sandbox/a.txt", "/tmp", 1, 1));
  REQUIRE(tree.is_regular_file("/sandbox/a.txt"));

  REQUIRE_NOTHROW(tree.create("/sandbox/foo/bar/baz/a", "/tmp", 1, 1));
  REQUIRE(tree.is_regular_file("/sandbox/foo/bar/baz/a"));

  REQUIRE_THROWS_AS(tree.create("/sandbox/foo/bar/baz/a/b", "/tmp", 1, 1), directory_ops_exception);
  REQUIRE_THROWS_AS(tree.create_directories("/sandbox/foo/bar/baz/a/b"),
                    directory_ops_exception);
}

TEST_CASE("open_file_test", "[file][dir]") {
  auto alloc = std::make_shared<dummy_block_allocator>(4);
  auto sm = std::make_shared<dummy_storage_manager>();
  directory_tree tree(alloc, sm);

  REQUIRE_NOTHROW(tree.create("/sandbox/a.txt", "/tmp", 1, 1));
  REQUIRE_NOTHROW(tree.create("/sandbox/foo/bar/baz/a", "/tmp", 1, 1));

  data_status s;
  REQUIRE_NOTHROW(s = tree.open("/sandbox/a.txt"));
  REQUIRE(s.chain_length() == 1);
  REQUIRE(s.mode() == storage_mode::in_memory);
  REQUIRE(s.persistent_store_prefix() == "/tmp");
  REQUIRE(s.data_blocks().size() == 1);

  REQUIRE_NOTHROW(s = tree.open("/sandbox/foo/bar/baz/a"));
  REQUIRE(s.chain_length() == 1);
  REQUIRE(s.mode() == storage_mode::in_memory);
  REQUIRE(s.persistent_store_prefix() == "/tmp");
  REQUIRE(s.data_blocks().size() == 1);

  REQUIRE_THROWS_AS(tree.open("/sandbox/b.txt"), directory_ops_exception);
}

TEST_CASE("open_or_create_file_test", "[file][dir]") {
  auto alloc = std::make_shared<dummy_block_allocator>(4);
  auto sm = std::make_shared<dummy_storage_manager>();
  directory_tree tree(alloc, sm);

  REQUIRE_NOTHROW(tree.create("/sandbox/a.txt", "/tmp", 1, 1));
  REQUIRE_NOTHROW(tree.create("/sandbox/foo/bar/baz/a", "/tmp", 1, 1));

  data_status s;
  REQUIRE_NOTHROW(s = tree.open_or_create("/sandbox/a.txt", "/tmp", 1, 1));
  REQUIRE(s.chain_length() == 1);
  REQUIRE(s.mode() == storage_mode::in_memory);
  REQUIRE(s.persistent_store_prefix() == "/tmp");
  REQUIRE(s.data_blocks().size() == 1);

  REQUIRE_NOTHROW(s = tree.open_or_create("/sandbox/foo/bar/baz/a", "/tmp", 1, 1));
  REQUIRE(s.chain_length() == 1);
  REQUIRE(s.mode() == storage_mode::in_memory);
  REQUIRE(s.persistent_store_prefix() == "/tmp");
  REQUIRE(s.data_blocks().size() == 1);

  REQUIRE_NOTHROW(s = tree.open_or_create("/sandbox/b.txt", "/tmp", 1, 1));
  REQUIRE(s.chain_length() == 1);
  REQUIRE(s.mode() == storage_mode::in_memory);
  REQUIRE(s.persistent_store_prefix() == "/tmp");
  REQUIRE(s.data_blocks().size() == 1);
}

TEST_CASE("exists_test", "[file][dir]") {
  auto alloc = std::make_shared<dummy_block_allocator>(4);
  auto sm = std::make_shared<dummy_storage_manager>();
  directory_tree tree(alloc, sm);

  REQUIRE_NOTHROW(tree.create("/sandbox/file", "/tmp", 1, 1));
  REQUIRE(tree.exists("/sandbox"));
  REQUIRE(tree.exists("/sandbox/file"));
  REQUIRE(!tree.exists("/sandbox/foo"));
}

TEST_CASE("last_write_time_test", "[file][dir][touch]") {
  auto alloc = std::make_shared<dummy_block_allocator>(4);
  auto sm = std::make_shared<dummy_storage_manager>();
  directory_tree tree(alloc, sm);

  std::uint64_t before = time_utils::now_ms();
  REQUIRE_NOTHROW(tree.create("/sandbox/file", "/tmp", 1, 1));
  std::uint64_t after = time_utils::now_ms();
  REQUIRE(before <= tree.last_write_time("/sandbox/file"));
  REQUIRE(tree.last_write_time("/sandbox/file") <= after);

  before = time_utils::now_ms();
  REQUIRE_NOTHROW(tree.touch("/sandbox/file"));
  after = time_utils::now_ms();
  REQUIRE(before <= tree.last_write_time("/sandbox/file"));
  REQUIRE(tree.last_write_time("/sandbox/file") <= after);

  before = time_utils::now_ms();
  REQUIRE_NOTHROW(tree.touch("/sandbox"));
  after = time_utils::now_ms();
  REQUIRE(before <= tree.last_write_time("/sandbox"));
  REQUIRE(tree.last_write_time("/sandbox") <= after);
  REQUIRE(before <= tree.last_write_time("/sandbox/file"));
  REQUIRE(tree.last_write_time("/sandbox/file") <= after);
  REQUIRE(tree.last_write_time("/sandbox") == tree.last_write_time("/sandbox/file"));
}

TEST_CASE("permissions_test", "[file][dir]") {
  auto alloc = std::make_shared<dummy_block_allocator>(4);
  auto sm = std::make_shared<dummy_storage_manager>();
  directory_tree tree(alloc, sm);

  REQUIRE_NOTHROW(tree.create("/sandbox/file", "/tmp", 1, 1));
  REQUIRE(tree.permissions("/sandbox") == perms::all);
  REQUIRE(tree.permissions("/sandbox/file") == perms::all);

  REQUIRE_NOTHROW(tree.permissions("/sandbox/file", perms::owner_all | perms::group_all, perm_options::replace));
  REQUIRE(tree.permissions("/sandbox/file") == (perms::owner_all | perms::group_all));

  REQUIRE_NOTHROW(tree.permissions("/sandbox/file", perms::others_all, perm_options::add));
  REQUIRE(tree.permissions("/sandbox/file") == (perms::owner_all | perms::group_all | perms::others_all));

  REQUIRE_NOTHROW(tree.permissions("/sandbox/file", perms::group_all | perms::others_all, perm_options::remove));
  REQUIRE(tree.permissions("/sandbox/file") == perms::owner_all);

  REQUIRE_NOTHROW(tree.permissions("/sandbox", perms::owner_all | perms::group_all, perm_options::replace));
  REQUIRE(tree.permissions("/sandbox") == (perms::owner_all | perms::group_all));

  REQUIRE_NOTHROW(tree.permissions("/sandbox", perms::others_all, perm_options::add));
  REQUIRE(tree.permissions("/sandbox") == (perms::owner_all | perms::group_all | perms::others_all));

  REQUIRE_NOTHROW(tree.permissions("/sandbox", perms::group_all | perms::others_all, perm_options::remove));
  REQUIRE(tree.permissions("/sandbox") == perms::owner_all);
}

TEST_CASE("path_remove_test", "[file][dir]") {
  auto alloc = std::make_shared<dummy_block_allocator>(4);
  auto sm = std::make_shared<dummy_storage_manager>();
  directory_tree tree(alloc, sm);

  REQUIRE_NOTHROW(tree.create("/sandbox/abcdef/example/a/b", "/tmp", 1, 1));
  REQUIRE(alloc->num_free_blocks() == 3);

  REQUIRE_NOTHROW(tree.remove("/sandbox/abcdef/example/a/b"));
  REQUIRE(!tree.exists("/sandbox/abcdef/example/a/b"));

  REQUIRE_NOTHROW(tree.remove("/sandbox/abcdef/example/a"));
  REQUIRE(!tree.exists("/sandbox/abcdef/example/a"));

  REQUIRE_THROWS_AS(tree.remove("/sandbox/abcdef"), directory_ops_exception);
  REQUIRE(tree.exists("/sandbox/abcdef"));

  REQUIRE_NOTHROW(tree.remove_all("/sandbox/abcdef"));
  REQUIRE(!tree.exists("/sandbox/abcdef"));
  REQUIRE(alloc->num_free_blocks() == 4);

  REQUIRE(sm->COMMANDS.size() == 2);
  REQUIRE(sm->COMMANDS[0] == "setup_block:0:/sandbox/abcdef/example/a/b:0:65536:0:0:nil");
  REQUIRE(sm->COMMANDS[1] == "reset:0");
}

TEST_CASE("path_flush_test", "[file][dir]") {
  auto alloc = std::make_shared<dummy_block_allocator>(4);
  auto sm = std::make_shared<dummy_storage_manager>();
  directory_tree tree(alloc, sm);
  REQUIRE_NOTHROW(tree.create("/sandbox/abcdef/example/a/b", "/tmp", 1, 1));
  REQUIRE_NOTHROW(tree.create("/sandbox/abcdef/example/c", "/tmp", 1, 1));
  REQUIRE(alloc->num_free_blocks() == 2);

  REQUIRE_NOTHROW(tree.flush("/sandbox/abcdef/example/c"));
  REQUIRE(tree.dstatus("/sandbox/abcdef/example/c").mode() == storage_mode::on_disk);

  REQUIRE_NOTHROW(tree.flush("/sandbox/abcdef/example/a"));
  REQUIRE(tree.dstatus("/sandbox/abcdef/example/a/b").mode() == storage_mode::on_disk);

  REQUIRE(alloc->num_free_blocks() == 4);
  REQUIRE(sm->COMMANDS.size() == 4);
  REQUIRE(sm->COMMANDS[0] == "setup_block:0:/sandbox/abcdef/example/a/b:0:65536:0:0:nil");
  REQUIRE(sm->COMMANDS[1] == "setup_block:1:/sandbox/abcdef/example/c:0:65536:1:0:nil");
  REQUIRE(sm->COMMANDS[2] == "flush:1:/tmp:/sandbox/abcdef/example/c");
  REQUIRE(sm->COMMANDS[3] == "flush:0:/tmp:/sandbox/abcdef/example/a/b");
}

TEST_CASE("rename_test", "[file][dir]") {
  auto alloc = std::make_shared<dummy_block_allocator>(4);
  auto sm = std::make_shared<dummy_storage_manager>();
  directory_tree tree(alloc, sm);

  REQUIRE_NOTHROW(tree.create("/sandbox/from/file1.txt", "/tmp", 1, 1));
  REQUIRE_NOTHROW(tree.create_directory("/sandbox/to"));

  REQUIRE_THROWS_AS(tree.rename("/sandbox/from/file1.txt", "/sandbox/to/"), directory_ops_exception);
  REQUIRE_NOTHROW(tree.rename("/sandbox/from/file1.txt", "/sandbox/to/file2.txt"));
  REQUIRE(tree.exists("/sandbox/to/file2.txt"));
  REQUIRE(!tree.exists("/sandbox/from/file1.txt"));

  REQUIRE_THROWS_AS(tree.rename("/sandbox/from", "/sandbox/to"), directory_ops_exception);
  REQUIRE_NOTHROW(tree.rename("/sandbox/from", "/sandbox/to/subdir"));
  REQUIRE(tree.exists("/sandbox/to/subdir"));
  REQUIRE(!tree.exists("/sandbox/from"));
}

TEST_CASE("status_test", "[file][dir]") {
  auto alloc = std::make_shared<dummy_block_allocator>(4);
  auto sm = std::make_shared<dummy_storage_manager>();
  directory_tree tree(alloc, sm);

  std::uint64_t before = time_utils::now_ms();
  REQUIRE_NOTHROW(tree.create("/sandbox/file", "/tmp", 1, 1));
  std::uint64_t after = time_utils::now_ms();
  REQUIRE(tree.status("/sandbox/file").permissions() == perms::all);
  REQUIRE(tree.status("/sandbox/file").type() == file_type::regular);
  REQUIRE(before <= tree.status("/sandbox/file").last_write_time());
  REQUIRE(tree.status("/sandbox/file").last_write_time() <= after);

  before = time_utils::now_ms();
  REQUIRE_NOTHROW(tree.create_directory("/sandbox/dir"));
  after = time_utils::now_ms();
  REQUIRE(tree.status("/sandbox/dir").permissions() == perms::all);
  REQUIRE(tree.status("/sandbox/dir").type() == file_type::directory);
  REQUIRE(before <= tree.status("/sandbox/dir").last_write_time());
  REQUIRE(tree.status("/sandbox/dir").last_write_time() <= after);
}

TEST_CASE("directory_entries_test", "[file][dir]") {
  auto alloc = std::make_shared<dummy_block_allocator>(4);
  auto sm = std::make_shared<dummy_storage_manager>();
  directory_tree tree(alloc, sm);

  std::uint64_t t0 = time_utils::now_ms();
  REQUIRE_NOTHROW(tree.create_directories("/sandbox/a/b"));
  std::uint64_t t1 = time_utils::now_ms();
  REQUIRE_NOTHROW(tree.create("/sandbox/file1.txt", "/tmp", 1, 1));
  std::uint64_t t2 = time_utils::now_ms();
  REQUIRE_NOTHROW(tree.create("/sandbox/file2.txt", "/tmp", 1, 1));
  std::uint64_t t3 = time_utils::now_ms();

  std::vector<directory_entry> entries;
  REQUIRE_NOTHROW(entries = tree.directory_entries("/sandbox"));
  REQUIRE(entries.size() == 3);
  REQUIRE(entries.at(0).name() == "a");
  REQUIRE(entries.at(0).type() == file_type::directory);
  REQUIRE(entries.at(0).permissions() == perms::all);
  REQUIRE(t0 <= entries.at(0).last_write_time());
  REQUIRE(entries.at(0).last_write_time() <= t1);
  REQUIRE(entries.at(1).name() == "file1.txt");
  REQUIRE(entries.at(1).type() == file_type::regular);
  REQUIRE(entries.at(1).permissions() == perms::all);
  REQUIRE(entries.at(1).last_write_time() <= t2);
  REQUIRE(t1 <= entries.at(1).last_write_time());
  REQUIRE(entries.at(2).name() == "file2.txt");
  REQUIRE(entries.at(2).type() == file_type::regular);
  REQUIRE(entries.at(2).permissions() == perms::all);
  REQUIRE(t2 <= entries.at(2).last_write_time());
  REQUIRE(entries.at(2).last_write_time() <= t3);
}

TEST_CASE("recursive_directory_entries_test", "[file][dir]") {
  auto alloc = std::make_shared<dummy_block_allocator>(4);
  auto sm = std::make_shared<dummy_storage_manager>();
  directory_tree tree(alloc, sm);

  std::uint64_t t0 = time_utils::now_ms();
  REQUIRE_NOTHROW(tree.create_directories("/sandbox/a/b"));
  std::uint64_t t1 = time_utils::now_ms();
  REQUIRE_NOTHROW(tree.create("/sandbox/file1.txt", "/tmp", 1, 1));
  std::uint64_t t2 = time_utils::now_ms();
  REQUIRE_NOTHROW(tree.create("/sandbox/file2.txt", "/tmp", 1, 1));
  std::uint64_t t3 = time_utils::now_ms();

  std::vector<directory_entry> entries;
  REQUIRE_NOTHROW(entries = tree.recursive_directory_entries("/sandbox"));
  REQUIRE(entries.size() == 4);
  REQUIRE(entries.at(0).name() == "a");
  REQUIRE(entries.at(0).type() == file_type::directory);
  REQUIRE(entries.at(0).permissions() == perms::all);
  REQUIRE(t0 <= entries.at(0).last_write_time());
  REQUIRE(entries.at(0).last_write_time() <= t1);
  REQUIRE(entries.at(1).name() == "b");
  REQUIRE(entries.at(1).type() == file_type::directory);
  REQUIRE(entries.at(1).permissions() == perms::all);
  REQUIRE(t0 <= entries.at(1).last_write_time());
  REQUIRE(entries.at(1).last_write_time() <= t1);
  REQUIRE(entries.at(2).name() == "file1.txt");
  REQUIRE(entries.at(2).type() == file_type::regular);
  REQUIRE(entries.at(2).permissions() == perms::all);
  REQUIRE(t1 <= entries.at(2).last_write_time());
  REQUIRE(entries.at(2).last_write_time() <= t2);
  REQUIRE(entries.at(3).name() == "file2.txt");
  REQUIRE(entries.at(3).type() == file_type::regular);
  REQUIRE(entries.at(3).permissions() == perms::all);
  REQUIRE(t2 <= entries.at(3).last_write_time());
  REQUIRE(entries.at(3).last_write_time() <= t3);
}

TEST_CASE("dstatus_test", "[file]") {
  auto alloc = std::make_shared<dummy_block_allocator>(4);
  auto sm = std::make_shared<dummy_storage_manager>();
  directory_tree tree(alloc, sm);

  REQUIRE_NOTHROW(tree.create("/sandbox/file.txt", "/tmp", 1, 1));
  REQUIRE_THROWS_AS(tree.dstatus("/sandbox"), directory_ops_exception);
  REQUIRE(tree.dstatus("/sandbox/file.txt").mode() == storage_mode::in_memory);
  REQUIRE(tree.dstatus("/sandbox/file.txt").persistent_store_prefix() == "/tmp");
  REQUIRE(tree.dstatus("/sandbox/file.txt").data_blocks().size() == 1);
  REQUIRE(tree.dstatus("/sandbox/file.txt").data_blocks().at(0).slot_range == std::make_pair(0, 65536));
  REQUIRE(tree.dstatus("/sandbox/file.txt").data_blocks().at(0).block_names[0] == "0");
}

TEST_CASE("file_type_test", "[file][dir]") {
  auto alloc = std::make_shared<dummy_block_allocator>(4);
  auto sm = std::make_shared<dummy_storage_manager>();
  directory_tree tree(alloc, sm);

  REQUIRE_NOTHROW(tree.create("/sandbox/file.txt", "/tmp", 1, 1));
  REQUIRE(tree.is_regular_file("/sandbox/file.txt"));
  REQUIRE_FALSE(tree.is_directory("/sandbox/file.txt"));

  REQUIRE(tree.is_directory("/sandbox"));
  REQUIRE_FALSE(tree.is_regular_file("/sandbox"));
}

TEST_CASE("add_block_to_file_test", "[file]") {
  auto alloc = std::make_shared<dummy_block_allocator>(4);
  auto sm = std::make_shared<dummy_storage_manager>();
  directory_tree tree(alloc, sm);
  REQUIRE_NOTHROW(tree.create("/sandbox/file.txt", "/tmp", 1, 1));
  REQUIRE_NOTHROW(tree.add_block_to_file("/sandbox/file.txt"));
  // Busy wait until number of blocks increases
  while (tree.dstatus("/sandbox/file.txt").data_blocks().size() == 1);
  REQUIRE(tree.dstatus("/sandbox/file.txt").data_blocks().size() == 2);
  REQUIRE(tree.dstatus("/sandbox/file.txt").data_blocks().at(0).status == chain_status::stable);
  REQUIRE(tree.dstatus("/sandbox/file.txt").data_blocks().at(0).slot_range == std::make_pair(0, 32768));
  REQUIRE(tree.dstatus("/sandbox/file.txt").data_blocks().at(1).status == chain_status::stable);
  REQUIRE(tree.dstatus("/sandbox/file.txt").data_blocks().at(1).slot_range == std::make_pair(32769, 65536));
  REQUIRE(sm->COMMANDS.size() == 7);
  REQUIRE(sm->COMMANDS[0] == "setup_block:0:/sandbox/file.txt:0:65536:0:0:nil");
  REQUIRE(sm->COMMANDS[1] == "storage_size:0");
  REQUIRE(sm->COMMANDS[2] == "set_importing:1:/sandbox/file.txt:32769:65536:1:0:nil");
  REQUIRE(sm->COMMANDS[3] == "set_exporting:0:1:32769:65536");
  REQUIRE(sm->COMMANDS[4] == "export_slots:0");
  REQUIRE(sm->COMMANDS[5] == "set_regular:0:0:32768");
  REQUIRE(sm->COMMANDS[6] == "set_regular:1:32769:65536");
}

TEST_CASE("split_block_test", "[file]") {
  auto alloc = std::make_shared<dummy_block_allocator>(4);
  auto sm = std::make_shared<dummy_storage_manager>();
  directory_tree tree(alloc, sm);
  REQUIRE_NOTHROW(tree.create("/sandbox/file.txt", "/tmp", 1, 1));
  REQUIRE_NOTHROW(tree.split_slot_range("/sandbox/file.txt", 0, 65536));
  // Busy wait until number of blocks increases
  while (tree.dstatus("/sandbox/file.txt").data_blocks().size() == 1);

  REQUIRE(tree.dstatus("/sandbox/file.txt").data_blocks().size() == 2);
  REQUIRE(tree.dstatus("/sandbox/file.txt").data_blocks().at(0).status == chain_status::stable);
  REQUIRE(tree.dstatus("/sandbox/file.txt").data_blocks().at(0).slot_range == std::make_pair(0, 32768));
  REQUIRE(tree.dstatus("/sandbox/file.txt").data_blocks().at(1).status == chain_status::stable);
  REQUIRE(tree.dstatus("/sandbox/file.txt").data_blocks().at(1).slot_range == std::make_pair(32769, 65536));
  REQUIRE(sm->COMMANDS.size() == 6);
  REQUIRE(sm->COMMANDS[0] == "setup_block:0:/sandbox/file.txt:0:65536:0:0:nil");
  REQUIRE(sm->COMMANDS[1] == "set_importing:1:/sandbox/file.txt:32769:65536:1:0:nil");
  REQUIRE(sm->COMMANDS[2] == "set_exporting:0:1:32769:65536");
  REQUIRE(sm->COMMANDS[3] == "export_slots:0");
  REQUIRE(sm->COMMANDS[4] == "set_regular:0:0:32768");
  REQUIRE(sm->COMMANDS[5] == "set_regular:1:32769:65536");
}
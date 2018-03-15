#include "binary_serde.h"

#include <fstream>

namespace elasticmem {
namespace kv {

std::size_t binary_serializer::serialize(const block_type &table, const std::string &path) {
  std::ofstream out(path, std::ofstream::trunc | std::ofstream::binary | std::ofstream::out);
  for (auto e: table) {
    std::size_t key_size = e.first.size();
    std::size_t value_size = e.second.size();
    out.write(reinterpret_cast<const char *>(&key_size), sizeof(size_t))
        .write(e.first.c_str(), key_size)
        .write(reinterpret_cast<const char *>(&value_size), sizeof(size_t))
        .write(e.second.c_str(), value_size);
  }
  auto sz = out.tellp();
  out.close();
  return static_cast<std::size_t>(sz);
}

std::size_t binary_deserializer::deserialize(const std::string &path, block_type &table) {
  std::ifstream in(path, std::ofstream::binary | std::ofstream::in);
  while (!in.eof()) {
    std::size_t key_size;
    std::size_t value_size;
    in.read(reinterpret_cast<char*>(&key_size), sizeof(key_size));
    std::string key;
    key.resize(key_size);
    in.read(&key[0], key_size);
    in.read(reinterpret_cast<char*>(&value_size), sizeof(value_size));
    std::string value;
    value.resize(value_size);
    in.read(&value[0], value_size);
    table.insert(key, value);
  }
  auto sz = in.tellg();
  in.close();
  return static_cast<std::size_t>(sz);
}

}
}
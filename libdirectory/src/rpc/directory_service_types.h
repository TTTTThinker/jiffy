/**
 * Autogenerated by Thrift Compiler (0.11.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef directory_service_TYPES_H
#define directory_service_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/stdcxx.h>


namespace elasticmem { namespace directory {

enum rpc_perm_options {
  rpc_replace = 0,
  rpc_add = 1,
  rpc_remove = 2
};

extern const std::map<int, const char*> _rpc_perm_options_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const rpc_perm_options val);

enum rpc_file_type {
  rpc_none = 0,
  rpc_regular = 1,
  rpc_directory = 2
};

extern const std::map<int, const char*> _rpc_file_type_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const rpc_file_type val);

enum rpc_storage_mode {
  rpc_in_memory = 0,
  rpc_in_memory_grace = 1,
  rpc_flushing = 2,
  rpc_on_disk = 3
};

extern const std::map<int, const char*> _rpc_storage_mode_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const rpc_storage_mode val);

typedef int32_t rpc_perms;

class rpc_file_status;

class rpc_data_status;

class rpc_dir_entry;

class directory_rpc_service_exception;

class rpc_file_metadata;

class lease_update;

class lease_ack;

class directory_lease_service_exception;


class rpc_file_status {
 public:

  rpc_file_status(const rpc_file_status&);
  rpc_file_status& operator=(const rpc_file_status&);
  rpc_file_status() : type((rpc_file_type)0), permissions(0), last_write_time(0) {
  }

  virtual ~rpc_file_status() throw();
  rpc_file_type type;
  rpc_perms permissions;
  int64_t last_write_time;

  void __set_type(const rpc_file_type val);

  void __set_permissions(const rpc_perms val);

  void __set_last_write_time(const int64_t val);

  bool operator == (const rpc_file_status & rhs) const
  {
    if (!(type == rhs.type))
      return false;
    if (!(permissions == rhs.permissions))
      return false;
    if (!(last_write_time == rhs.last_write_time))
      return false;
    return true;
  }
  bool operator != (const rpc_file_status &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const rpc_file_status & ) const;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(rpc_file_status &a, rpc_file_status &b);

std::ostream& operator<<(std::ostream& out, const rpc_file_status& obj);


class rpc_data_status {
 public:

  rpc_data_status(const rpc_data_status&);
  rpc_data_status& operator=(const rpc_data_status&);
  rpc_data_status() : storage_mode((rpc_storage_mode)0), persistent_store_prefix() {
  }

  virtual ~rpc_data_status() throw();
  rpc_storage_mode storage_mode;
  std::string persistent_store_prefix;
  std::vector<std::string>  data_blocks;

  void __set_storage_mode(const rpc_storage_mode val);

  void __set_persistent_store_prefix(const std::string& val);

  void __set_data_blocks(const std::vector<std::string> & val);

  bool operator == (const rpc_data_status & rhs) const
  {
    if (!(storage_mode == rhs.storage_mode))
      return false;
    if (!(persistent_store_prefix == rhs.persistent_store_prefix))
      return false;
    if (!(data_blocks == rhs.data_blocks))
      return false;
    return true;
  }
  bool operator != (const rpc_data_status &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const rpc_data_status & ) const;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(rpc_data_status &a, rpc_data_status &b);

std::ostream& operator<<(std::ostream& out, const rpc_data_status& obj);


class rpc_dir_entry {
 public:

  rpc_dir_entry(const rpc_dir_entry&);
  rpc_dir_entry& operator=(const rpc_dir_entry&);
  rpc_dir_entry() : name() {
  }

  virtual ~rpc_dir_entry() throw();
  std::string name;
  rpc_file_status status;

  void __set_name(const std::string& val);

  void __set_status(const rpc_file_status& val);

  bool operator == (const rpc_dir_entry & rhs) const
  {
    if (!(name == rhs.name))
      return false;
    if (!(status == rhs.status))
      return false;
    return true;
  }
  bool operator != (const rpc_dir_entry &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const rpc_dir_entry & ) const;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(rpc_dir_entry &a, rpc_dir_entry &b);

std::ostream& operator<<(std::ostream& out, const rpc_dir_entry& obj);


class directory_rpc_service_exception : public ::apache::thrift::TException {
 public:

  directory_rpc_service_exception(const directory_rpc_service_exception&);
  directory_rpc_service_exception& operator=(const directory_rpc_service_exception&);
  directory_rpc_service_exception() : msg() {
  }

  virtual ~directory_rpc_service_exception() throw();
  std::string msg;

  void __set_msg(const std::string& val);

  bool operator == (const directory_rpc_service_exception & rhs) const
  {
    if (!(msg == rhs.msg))
      return false;
    return true;
  }
  bool operator != (const directory_rpc_service_exception &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const directory_rpc_service_exception & ) const;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const throw();
};

void swap(directory_rpc_service_exception &a, directory_rpc_service_exception &b);

std::ostream& operator<<(std::ostream& out, const directory_rpc_service_exception& obj);


class rpc_file_metadata {
 public:

  rpc_file_metadata(const rpc_file_metadata&);
  rpc_file_metadata& operator=(const rpc_file_metadata&);
  rpc_file_metadata() : path(), bytes(0) {
  }

  virtual ~rpc_file_metadata() throw();
  std::string path;
  int64_t bytes;

  void __set_path(const std::string& val);

  void __set_bytes(const int64_t val);

  bool operator == (const rpc_file_metadata & rhs) const
  {
    if (!(path == rhs.path))
      return false;
    if (!(bytes == rhs.bytes))
      return false;
    return true;
  }
  bool operator != (const rpc_file_metadata &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const rpc_file_metadata & ) const;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(rpc_file_metadata &a, rpc_file_metadata &b);

std::ostream& operator<<(std::ostream& out, const rpc_file_metadata& obj);


class lease_update {
 public:

  lease_update(const lease_update&);
  lease_update& operator=(const lease_update&);
  lease_update() {
  }

  virtual ~lease_update() throw();
  std::vector<rpc_file_metadata>  to_renew;
  std::vector<std::string>  to_flush;
  std::vector<std::string>  to_remove;

  void __set_to_renew(const std::vector<rpc_file_metadata> & val);

  void __set_to_flush(const std::vector<std::string> & val);

  void __set_to_remove(const std::vector<std::string> & val);

  bool operator == (const lease_update & rhs) const
  {
    if (!(to_renew == rhs.to_renew))
      return false;
    if (!(to_flush == rhs.to_flush))
      return false;
    if (!(to_remove == rhs.to_remove))
      return false;
    return true;
  }
  bool operator != (const lease_update &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const lease_update & ) const;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(lease_update &a, lease_update &b);

std::ostream& operator<<(std::ostream& out, const lease_update& obj);


class lease_ack {
 public:

  lease_ack(const lease_ack&);
  lease_ack& operator=(const lease_ack&);
  lease_ack() : flushed(0), removed(0) {
  }

  virtual ~lease_ack() throw();
  std::vector<rpc_file_metadata>  renewed;
  int64_t flushed;
  int64_t removed;

  void __set_renewed(const std::vector<rpc_file_metadata> & val);

  void __set_flushed(const int64_t val);

  void __set_removed(const int64_t val);

  bool operator == (const lease_ack & rhs) const
  {
    if (!(renewed == rhs.renewed))
      return false;
    if (!(flushed == rhs.flushed))
      return false;
    if (!(removed == rhs.removed))
      return false;
    return true;
  }
  bool operator != (const lease_ack &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const lease_ack & ) const;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(lease_ack &a, lease_ack &b);

std::ostream& operator<<(std::ostream& out, const lease_ack& obj);

typedef struct _directory_lease_service_exception__isset {
  _directory_lease_service_exception__isset() : msg(false) {}
  bool msg :1;
} _directory_lease_service_exception__isset;

class directory_lease_service_exception : public ::apache::thrift::TException {
 public:

  directory_lease_service_exception(const directory_lease_service_exception&);
  directory_lease_service_exception& operator=(const directory_lease_service_exception&);
  directory_lease_service_exception() : msg() {
  }

  virtual ~directory_lease_service_exception() throw();
  std::string msg;

  _directory_lease_service_exception__isset __isset;

  void __set_msg(const std::string& val);

  bool operator == (const directory_lease_service_exception & rhs) const
  {
    if (!(msg == rhs.msg))
      return false;
    return true;
  }
  bool operator != (const directory_lease_service_exception &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const directory_lease_service_exception & ) const;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const throw();
};

void swap(directory_lease_service_exception &a, directory_lease_service_exception &b);

std::ostream& operator<<(std::ostream& out, const directory_lease_service_exception& obj);

}} // namespace

#include "directory_service_types.tcc"

#endif

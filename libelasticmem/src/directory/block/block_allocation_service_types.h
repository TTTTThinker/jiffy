/**
 * Autogenerated by Thrift Compiler (0.11.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef block_allocation_service_TYPES_H
#define block_allocation_service_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/stdcxx.h>


namespace elasticmem { namespace directory {

class block_allocation_service_exception;

typedef struct _block_allocation_service_exception__isset {
  _block_allocation_service_exception__isset() : msg(false) {}
  bool msg :1;
} _block_allocation_service_exception__isset;

class block_allocation_service_exception : public ::apache::thrift::TException {
 public:

  block_allocation_service_exception(const block_allocation_service_exception&);
  block_allocation_service_exception& operator=(const block_allocation_service_exception&);
  block_allocation_service_exception() : msg() {
  }

  virtual ~block_allocation_service_exception() throw();
  std::string msg;

  _block_allocation_service_exception__isset __isset;

  void __set_msg(const std::string& val);

  bool operator == (const block_allocation_service_exception & rhs) const
  {
    if (!(msg == rhs.msg))
      return false;
    return true;
  }
  bool operator != (const block_allocation_service_exception &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const block_allocation_service_exception & ) const;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const throw();
};

void swap(block_allocation_service_exception &a, block_allocation_service_exception &b);

std::ostream& operator<<(std::ostream& out, const block_allocation_service_exception& obj);

}} // namespace

#include "block_allocation_service_types.tcc"

#endif

/**
 * Autogenerated by Thrift Compiler (0.11.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef lease_service_H
#define lease_service_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "lease_service_types.h"

namespace elasticmem { namespace directory {

#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class lease_serviceIf {
 public:
  virtual ~lease_serviceIf() {}
  virtual void renew_leases(rpc_lease_ack& _return, const std::vector<std::string> & to_renew) = 0;
};

class lease_serviceIfFactory {
 public:
  typedef lease_serviceIf Handler;

  virtual ~lease_serviceIfFactory() {}

  virtual lease_serviceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(lease_serviceIf* /* handler */) = 0;
};

class lease_serviceIfSingletonFactory : virtual public lease_serviceIfFactory {
 public:
  lease_serviceIfSingletonFactory(const ::apache::thrift::stdcxx::shared_ptr<lease_serviceIf>& iface) : iface_(iface) {}
  virtual ~lease_serviceIfSingletonFactory() {}

  virtual lease_serviceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(lease_serviceIf* /* handler */) {}

 protected:
  ::apache::thrift::stdcxx::shared_ptr<lease_serviceIf> iface_;
};

class lease_serviceNull : virtual public lease_serviceIf {
 public:
  virtual ~lease_serviceNull() {}
  void renew_leases(rpc_lease_ack& /* _return */, const std::vector<std::string> & /* to_renew */) {
    return;
  }
};

typedef struct _lease_service_renew_leases_args__isset {
  _lease_service_renew_leases_args__isset() : to_renew(false) {}
  bool to_renew :1;
} _lease_service_renew_leases_args__isset;

class lease_service_renew_leases_args {
 public:

  lease_service_renew_leases_args(const lease_service_renew_leases_args&);
  lease_service_renew_leases_args& operator=(const lease_service_renew_leases_args&);
  lease_service_renew_leases_args() {
  }

  virtual ~lease_service_renew_leases_args() throw();
  std::vector<std::string>  to_renew;

  _lease_service_renew_leases_args__isset __isset;

  void __set_to_renew(const std::vector<std::string> & val);

  bool operator == (const lease_service_renew_leases_args & rhs) const
  {
    if (!(to_renew == rhs.to_renew))
      return false;
    return true;
  }
  bool operator != (const lease_service_renew_leases_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const lease_service_renew_leases_args & ) const;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

};


class lease_service_renew_leases_pargs {
 public:


  virtual ~lease_service_renew_leases_pargs() throw();
  const std::vector<std::string> * to_renew;

  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

};

typedef struct _lease_service_renew_leases_result__isset {
  _lease_service_renew_leases_result__isset() : success(false), ex(false) {}
  bool success :1;
  bool ex :1;
} _lease_service_renew_leases_result__isset;

class lease_service_renew_leases_result {
 public:

  lease_service_renew_leases_result(const lease_service_renew_leases_result&);
  lease_service_renew_leases_result& operator=(const lease_service_renew_leases_result&);
  lease_service_renew_leases_result() {
  }

  virtual ~lease_service_renew_leases_result() throw();
  rpc_lease_ack success;
  lease_service_exception ex;

  _lease_service_renew_leases_result__isset __isset;

  void __set_success(const rpc_lease_ack& val);

  void __set_ex(const lease_service_exception& val);

  bool operator == (const lease_service_renew_leases_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(ex == rhs.ex))
      return false;
    return true;
  }
  bool operator != (const lease_service_renew_leases_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const lease_service_renew_leases_result & ) const;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t write(Protocol_* oprot) const;

};

typedef struct _lease_service_renew_leases_presult__isset {
  _lease_service_renew_leases_presult__isset() : success(false), ex(false) {}
  bool success :1;
  bool ex :1;
} _lease_service_renew_leases_presult__isset;

class lease_service_renew_leases_presult {
 public:


  virtual ~lease_service_renew_leases_presult() throw();
  rpc_lease_ack* success;
  lease_service_exception ex;

  _lease_service_renew_leases_presult__isset __isset;

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);

};

template <class Protocol_>
class lease_serviceClientT : virtual public lease_serviceIf {
 public:
  lease_serviceClientT(apache::thrift::stdcxx::shared_ptr< Protocol_> prot) {
    setProtocolT(prot);
  }
  lease_serviceClientT(apache::thrift::stdcxx::shared_ptr< Protocol_> iprot, apache::thrift::stdcxx::shared_ptr< Protocol_> oprot) {
    setProtocolT(iprot,oprot);
  }
 private:
  void setProtocolT(apache::thrift::stdcxx::shared_ptr< Protocol_> prot) {
  setProtocolT(prot,prot);
  }
  void setProtocolT(apache::thrift::stdcxx::shared_ptr< Protocol_> iprot, apache::thrift::stdcxx::shared_ptr< Protocol_> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return this->piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return this->poprot_;
  }
  void renew_leases(rpc_lease_ack& _return, const std::vector<std::string> & to_renew);
  void send_renew_leases(const std::vector<std::string> & to_renew);
  void recv_renew_leases(rpc_lease_ack& _return);
 protected:
  apache::thrift::stdcxx::shared_ptr< Protocol_> piprot_;
  apache::thrift::stdcxx::shared_ptr< Protocol_> poprot_;
  Protocol_* iprot_;
  Protocol_* oprot_;
};

typedef lease_serviceClientT< ::apache::thrift::protocol::TProtocol> lease_serviceClient;

template <class Protocol_>
class lease_serviceProcessorT : public ::apache::thrift::TDispatchProcessorT<Protocol_> {
 protected:
  ::apache::thrift::stdcxx::shared_ptr<lease_serviceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
  virtual bool dispatchCallTemplated(Protocol_* iprot, Protocol_* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (lease_serviceProcessorT::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef void (lease_serviceProcessorT::*SpecializedProcessFunction)(int32_t, Protocol_*, Protocol_*, void*);
  struct ProcessFunctions {
    ProcessFunction generic;
    SpecializedProcessFunction specialized;
    ProcessFunctions(ProcessFunction g, SpecializedProcessFunction s) :
      generic(g),
      specialized(s) {}
    ProcessFunctions() : generic(NULL), specialized(NULL) {}
  };
  typedef std::map<std::string, ProcessFunctions> ProcessMap;
  ProcessMap processMap_;
  void process_renew_leases(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_renew_leases(int32_t seqid, Protocol_* iprot, Protocol_* oprot, void* callContext);
 public:
  lease_serviceProcessorT(::apache::thrift::stdcxx::shared_ptr<lease_serviceIf> iface) :
    iface_(iface) {
    processMap_["renew_leases"] = ProcessFunctions(
      &lease_serviceProcessorT::process_renew_leases,
      &lease_serviceProcessorT::process_renew_leases);
  }

  virtual ~lease_serviceProcessorT() {}
};

typedef lease_serviceProcessorT< ::apache::thrift::protocol::TDummyProtocol > lease_serviceProcessor;

template <class Protocol_>
class lease_serviceProcessorFactoryT : public ::apache::thrift::TProcessorFactory {
 public:
  lease_serviceProcessorFactoryT(const ::apache::thrift::stdcxx::shared_ptr< lease_serviceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::apache::thrift::stdcxx::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::apache::thrift::stdcxx::shared_ptr< lease_serviceIfFactory > handlerFactory_;
};

typedef lease_serviceProcessorFactoryT< ::apache::thrift::protocol::TDummyProtocol > lease_serviceProcessorFactory;

class lease_serviceMultiface : virtual public lease_serviceIf {
 public:
  lease_serviceMultiface(std::vector<apache::thrift::stdcxx::shared_ptr<lease_serviceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~lease_serviceMultiface() {}
 protected:
  std::vector<apache::thrift::stdcxx::shared_ptr<lease_serviceIf> > ifaces_;
  lease_serviceMultiface() {}
  void add(::apache::thrift::stdcxx::shared_ptr<lease_serviceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void renew_leases(rpc_lease_ack& _return, const std::vector<std::string> & to_renew) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->renew_leases(_return, to_renew);
    }
    ifaces_[i]->renew_leases(_return, to_renew);
    return;
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
template <class Protocol_>
class lease_serviceConcurrentClientT : virtual public lease_serviceIf {
 public:
  lease_serviceConcurrentClientT(apache::thrift::stdcxx::shared_ptr< Protocol_> prot) {
    setProtocolT(prot);
  }
  lease_serviceConcurrentClientT(apache::thrift::stdcxx::shared_ptr< Protocol_> iprot, apache::thrift::stdcxx::shared_ptr< Protocol_> oprot) {
    setProtocolT(iprot,oprot);
  }
 private:
  void setProtocolT(apache::thrift::stdcxx::shared_ptr< Protocol_> prot) {
  setProtocolT(prot,prot);
  }
  void setProtocolT(apache::thrift::stdcxx::shared_ptr< Protocol_> iprot, apache::thrift::stdcxx::shared_ptr< Protocol_> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return this->piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return this->poprot_;
  }
  void renew_leases(rpc_lease_ack& _return, const std::vector<std::string> & to_renew);
  int32_t send_renew_leases(const std::vector<std::string> & to_renew);
  void recv_renew_leases(rpc_lease_ack& _return, const int32_t seqid);
 protected:
  apache::thrift::stdcxx::shared_ptr< Protocol_> piprot_;
  apache::thrift::stdcxx::shared_ptr< Protocol_> poprot_;
  Protocol_* iprot_;
  Protocol_* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

typedef lease_serviceConcurrentClientT< ::apache::thrift::protocol::TProtocol> lease_serviceConcurrentClient;

#ifdef _MSC_VER
  #pragma warning( pop )
#endif

}} // namespace

#include "lease_service.tcc"
#include "lease_service_types.tcc"

#endif

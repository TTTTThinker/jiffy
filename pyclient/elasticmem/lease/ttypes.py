#
# Autogenerated by Thrift Compiler (0.11.0)
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#
#  options string: py
#

from thrift.Thrift import TType, TMessageType, TFrozenDict, TException, TApplicationException
from thrift.protocol.TProtocol import TProtocolException
from thrift.TRecursive import fix_spec

import sys

from thrift.transport import TTransport
all_structs = []


class rpc_lease_update(object):
    """
    Attributes:
     - to_renew
     - to_flush
     - to_remove
    """


    def __init__(self, to_renew=None, to_flush=None, to_remove=None,):
        self.to_renew = to_renew
        self.to_flush = to_flush
        self.to_remove = to_remove

    def read(self, iprot):
        if iprot._fast_decode is not None and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None:
            iprot._fast_decode(self, iprot, [self.__class__, self.thrift_spec])
            return
        iprot.readStructBegin()
        while True:
            (fname, ftype, fid) = iprot.readFieldBegin()
            if ftype == TType.STOP:
                break
            if fid == 1:
                if ftype == TType.LIST:
                    self.to_renew = []
                    (_etype3, _size0) = iprot.readListBegin()
                    for _i4 in range(_size0):
                        _elem5 = iprot.readString().decode('utf-8') if sys.version_info[0] == 2 else iprot.readString()
                        self.to_renew.append(_elem5)
                    iprot.readListEnd()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.LIST:
                    self.to_flush = []
                    (_etype9, _size6) = iprot.readListBegin()
                    for _i10 in range(_size6):
                        _elem11 = iprot.readString().decode('utf-8') if sys.version_info[0] == 2 else iprot.readString()
                        self.to_flush.append(_elem11)
                    iprot.readListEnd()
                else:
                    iprot.skip(ftype)
            elif fid == 3:
                if ftype == TType.LIST:
                    self.to_remove = []
                    (_etype15, _size12) = iprot.readListBegin()
                    for _i16 in range(_size12):
                        _elem17 = iprot.readString().decode('utf-8') if sys.version_info[0] == 2 else iprot.readString()
                        self.to_remove.append(_elem17)
                    iprot.readListEnd()
                else:
                    iprot.skip(ftype)
            else:
                iprot.skip(ftype)
            iprot.readFieldEnd()
        iprot.readStructEnd()

    def write(self, oprot):
        if oprot._fast_encode is not None and self.thrift_spec is not None:
            oprot.trans.write(oprot._fast_encode(self, [self.__class__, self.thrift_spec]))
            return
        oprot.writeStructBegin('rpc_lease_update')
        if self.to_renew is not None:
            oprot.writeFieldBegin('to_renew', TType.LIST, 1)
            oprot.writeListBegin(TType.STRING, len(self.to_renew))
            for iter18 in self.to_renew:
                oprot.writeString(iter18.encode('utf-8') if sys.version_info[0] == 2 else iter18)
            oprot.writeListEnd()
            oprot.writeFieldEnd()
        if self.to_flush is not None:
            oprot.writeFieldBegin('to_flush', TType.LIST, 2)
            oprot.writeListBegin(TType.STRING, len(self.to_flush))
            for iter19 in self.to_flush:
                oprot.writeString(iter19.encode('utf-8') if sys.version_info[0] == 2 else iter19)
            oprot.writeListEnd()
            oprot.writeFieldEnd()
        if self.to_remove is not None:
            oprot.writeFieldBegin('to_remove', TType.LIST, 3)
            oprot.writeListBegin(TType.STRING, len(self.to_remove))
            for iter20 in self.to_remove:
                oprot.writeString(iter20.encode('utf-8') if sys.version_info[0] == 2 else iter20)
            oprot.writeListEnd()
            oprot.writeFieldEnd()
        oprot.writeFieldStop()
        oprot.writeStructEnd()

    def validate(self):
        if self.to_renew is None:
            raise TProtocolException(message='Required field to_renew is unset!')
        if self.to_flush is None:
            raise TProtocolException(message='Required field to_flush is unset!')
        if self.to_remove is None:
            raise TProtocolException(message='Required field to_remove is unset!')
        return

    def __repr__(self):
        L = ['%s=%r' % (key, value)
             for key, value in self.__dict__.items()]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

    def __eq__(self, other):
        return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

    def __ne__(self, other):
        return not (self == other)


class rpc_lease_ack(object):
    """
    Attributes:
     - renewed
     - flushed
     - removed
    """


    def __init__(self, renewed=None, flushed=None, removed=None,):
        self.renewed = renewed
        self.flushed = flushed
        self.removed = removed

    def read(self, iprot):
        if iprot._fast_decode is not None and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None:
            iprot._fast_decode(self, iprot, [self.__class__, self.thrift_spec])
            return
        iprot.readStructBegin()
        while True:
            (fname, ftype, fid) = iprot.readFieldBegin()
            if ftype == TType.STOP:
                break
            if fid == 1:
                if ftype == TType.I64:
                    self.renewed = iprot.readI64()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.I64:
                    self.flushed = iprot.readI64()
                else:
                    iprot.skip(ftype)
            elif fid == 3:
                if ftype == TType.I64:
                    self.removed = iprot.readI64()
                else:
                    iprot.skip(ftype)
            else:
                iprot.skip(ftype)
            iprot.readFieldEnd()
        iprot.readStructEnd()

    def write(self, oprot):
        if oprot._fast_encode is not None and self.thrift_spec is not None:
            oprot.trans.write(oprot._fast_encode(self, [self.__class__, self.thrift_spec]))
            return
        oprot.writeStructBegin('rpc_lease_ack')
        if self.renewed is not None:
            oprot.writeFieldBegin('renewed', TType.I64, 1)
            oprot.writeI64(self.renewed)
            oprot.writeFieldEnd()
        if self.flushed is not None:
            oprot.writeFieldBegin('flushed', TType.I64, 2)
            oprot.writeI64(self.flushed)
            oprot.writeFieldEnd()
        if self.removed is not None:
            oprot.writeFieldBegin('removed', TType.I64, 3)
            oprot.writeI64(self.removed)
            oprot.writeFieldEnd()
        oprot.writeFieldStop()
        oprot.writeStructEnd()

    def validate(self):
        if self.renewed is None:
            raise TProtocolException(message='Required field renewed is unset!')
        if self.flushed is None:
            raise TProtocolException(message='Required field flushed is unset!')
        if self.removed is None:
            raise TProtocolException(message='Required field removed is unset!')
        return

    def __repr__(self):
        L = ['%s=%r' % (key, value)
             for key, value in self.__dict__.items()]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

    def __eq__(self, other):
        return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

    def __ne__(self, other):
        return not (self == other)


class directory_lease_service_exception(TException):
    """
    Attributes:
     - msg
    """


    def __init__(self, msg=None,):
        self.msg = msg

    def read(self, iprot):
        if iprot._fast_decode is not None and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None:
            iprot._fast_decode(self, iprot, [self.__class__, self.thrift_spec])
            return
        iprot.readStructBegin()
        while True:
            (fname, ftype, fid) = iprot.readFieldBegin()
            if ftype == TType.STOP:
                break
            if fid == 1:
                if ftype == TType.STRING:
                    self.msg = iprot.readString().decode('utf-8') if sys.version_info[0] == 2 else iprot.readString()
                else:
                    iprot.skip(ftype)
            else:
                iprot.skip(ftype)
            iprot.readFieldEnd()
        iprot.readStructEnd()

    def write(self, oprot):
        if oprot._fast_encode is not None and self.thrift_spec is not None:
            oprot.trans.write(oprot._fast_encode(self, [self.__class__, self.thrift_spec]))
            return
        oprot.writeStructBegin('directory_lease_service_exception')
        if self.msg is not None:
            oprot.writeFieldBegin('msg', TType.STRING, 1)
            oprot.writeString(self.msg.encode('utf-8') if sys.version_info[0] == 2 else self.msg)
            oprot.writeFieldEnd()
        oprot.writeFieldStop()
        oprot.writeStructEnd()

    def validate(self):
        return

    def __str__(self):
        return repr(self)

    def __repr__(self):
        L = ['%s=%r' % (key, value)
             for key, value in self.__dict__.items()]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

    def __eq__(self, other):
        return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

    def __ne__(self, other):
        return not (self == other)
all_structs.append(rpc_lease_update)
rpc_lease_update.thrift_spec = (
    None,  # 0
    (1, TType.LIST, 'to_renew', (TType.STRING, 'UTF8', False), None, ),  # 1
    (2, TType.LIST, 'to_flush', (TType.STRING, 'UTF8', False), None, ),  # 2
    (3, TType.LIST, 'to_remove', (TType.STRING, 'UTF8', False), None, ),  # 3
)
all_structs.append(rpc_lease_ack)
rpc_lease_ack.thrift_spec = (
    None,  # 0
    (1, TType.I64, 'renewed', None, None, ),  # 1
    (2, TType.I64, 'flushed', None, None, ),  # 2
    (3, TType.I64, 'removed', None, None, ),  # 3
)
all_structs.append(directory_lease_service_exception)
directory_lease_service_exception.thrift_spec = (
    None,  # 0
    (1, TType.STRING, 'msg', 'UTF8', None, ),  # 1
)
fix_spec(all_structs)
del all_structs

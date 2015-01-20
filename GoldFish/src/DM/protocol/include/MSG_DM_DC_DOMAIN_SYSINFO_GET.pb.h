// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MSG_DM_DC_DOMAIN_SYSINFO_GET.proto

#ifndef PROTOBUF_MSG_5fDM_5fDC_5fDOMAIN_5fSYSINFO_5fGET_2eproto__INCLUDED
#define PROTOBUF_MSG_5fDM_5fDC_5fDOMAIN_5fSYSINFO_5fGET_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_MSG_5fDM_5fDC_5fDOMAIN_5fSYSINFO_5fGET_2eproto();
void protobuf_AssignDesc_MSG_5fDM_5fDC_5fDOMAIN_5fSYSINFO_5fGET_2eproto();
void protobuf_ShutdownFile_MSG_5fDM_5fDC_5fDOMAIN_5fSYSINFO_5fGET_2eproto();

class MSG_DM_DC_DOMAIN_SYSINFO_GET;
class MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK;
class MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO;

// ===================================================================

class MSG_DM_DC_DOMAIN_SYSINFO_GET : public ::google::protobuf::Message {
 public:
  MSG_DM_DC_DOMAIN_SYSINFO_GET();
  virtual ~MSG_DM_DC_DOMAIN_SYSINFO_GET();
  
  MSG_DM_DC_DOMAIN_SYSINFO_GET(const MSG_DM_DC_DOMAIN_SYSINFO_GET& from);
  
  inline MSG_DM_DC_DOMAIN_SYSINFO_GET& operator=(const MSG_DM_DC_DOMAIN_SYSINFO_GET& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const MSG_DM_DC_DOMAIN_SYSINFO_GET& default_instance();
  
  void Swap(MSG_DM_DC_DOMAIN_SYSINFO_GET* other);
  
  // implements Message ----------------------------------------------
  
  MSG_DM_DC_DOMAIN_SYSINFO_GET* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MSG_DM_DC_DOMAIN_SYSINFO_GET& from);
  void MergeFrom(const MSG_DM_DC_DOMAIN_SYSINFO_GET& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional string timestamp = 1;
  inline bool has_timestamp() const;
  inline void clear_timestamp();
  static const int kTimestampFieldNumber = 1;
  inline const ::std::string& timestamp() const;
  inline void set_timestamp(const ::std::string& value);
  inline void set_timestamp(const char* value);
  inline void set_timestamp(const char* value, size_t size);
  inline ::std::string* mutable_timestamp();
  inline ::std::string* release_timestamp();
  
  // @@protoc_insertion_point(class_scope:MSG_DM_DC_DOMAIN_SYSINFO_GET)
 private:
  inline void set_has_timestamp();
  inline void clear_has_timestamp();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* timestamp_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_MSG_5fDM_5fDC_5fDOMAIN_5fSYSINFO_5fGET_2eproto();
  friend void protobuf_AssignDesc_MSG_5fDM_5fDC_5fDOMAIN_5fSYSINFO_5fGET_2eproto();
  friend void protobuf_ShutdownFile_MSG_5fDM_5fDC_5fDOMAIN_5fSYSINFO_5fGET_2eproto();
  
  void InitAsDefaultInstance();
  static MSG_DM_DC_DOMAIN_SYSINFO_GET* default_instance_;
};
// -------------------------------------------------------------------

class MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO : public ::google::protobuf::Message {
 public:
  MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO();
  virtual ~MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO();
  
  MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO(const MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO& from);
  
  inline MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO& operator=(const MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO& default_instance();
  
  void Swap(MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO* other);
  
  // implements Message ----------------------------------------------
  
  MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO& from);
  void MergeFrom(const MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional string nodeStatus = 1;
  inline bool has_nodestatus() const;
  inline void clear_nodestatus();
  static const int kNodeStatusFieldNumber = 1;
  inline const ::std::string& nodestatus() const;
  inline void set_nodestatus(const ::std::string& value);
  inline void set_nodestatus(const char* value);
  inline void set_nodestatus(const char* value, size_t size);
  inline ::std::string* mutable_nodestatus();
  inline ::std::string* release_nodestatus();
  
  // optional uint32 core = 2;
  inline bool has_core() const;
  inline void clear_core();
  static const int kCoreFieldNumber = 2;
  inline ::google::protobuf::uint32 core() const;
  inline void set_core(::google::protobuf::uint32 value);
  
  // optional uint32 memSize = 3;
  inline bool has_memsize() const;
  inline void clear_memsize();
  static const int kMemSizeFieldNumber = 3;
  inline ::google::protobuf::uint32 memsize() const;
  inline void set_memsize(::google::protobuf::uint32 value);
  
  // @@protoc_insertion_point(class_scope:MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK.CS_SYS_INFO)
 private:
  inline void set_has_nodestatus();
  inline void clear_has_nodestatus();
  inline void set_has_core();
  inline void clear_has_core();
  inline void set_has_memsize();
  inline void clear_has_memsize();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* nodestatus_;
  ::google::protobuf::uint32 core_;
  ::google::protobuf::uint32 memsize_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_MSG_5fDM_5fDC_5fDOMAIN_5fSYSINFO_5fGET_2eproto();
  friend void protobuf_AssignDesc_MSG_5fDM_5fDC_5fDOMAIN_5fSYSINFO_5fGET_2eproto();
  friend void protobuf_ShutdownFile_MSG_5fDM_5fDC_5fDOMAIN_5fSYSINFO_5fGET_2eproto();
  
  void InitAsDefaultInstance();
  static MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO* default_instance_;
};
// -------------------------------------------------------------------

class MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK : public ::google::protobuf::Message {
 public:
  MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK();
  virtual ~MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK();
  
  MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK(const MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK& from);
  
  inline MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK& operator=(const MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK& default_instance();
  
  void Swap(MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK* other);
  
  // implements Message ----------------------------------------------
  
  MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK& from);
  void MergeFrom(const MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  typedef MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO CS_SYS_INFO;
  
  // accessors -------------------------------------------------------
  
  // optional int32 statusCode = 1;
  inline bool has_statuscode() const;
  inline void clear_statuscode();
  static const int kStatusCodeFieldNumber = 1;
  inline ::google::protobuf::int32 statuscode() const;
  inline void set_statuscode(::google::protobuf::int32 value);
  
  // repeated .MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK.CS_SYS_INFO singleNodeSysInfo = 2;
  inline int singlenodesysinfo_size() const;
  inline void clear_singlenodesysinfo();
  static const int kSingleNodeSysInfoFieldNumber = 2;
  inline const ::MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO& singlenodesysinfo(int index) const;
  inline ::MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO* mutable_singlenodesysinfo(int index);
  inline ::MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO* add_singlenodesysinfo();
  inline const ::google::protobuf::RepeatedPtrField< ::MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO >&
      singlenodesysinfo() const;
  inline ::google::protobuf::RepeatedPtrField< ::MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO >*
      mutable_singlenodesysinfo();
  
  // optional string timeStamp = 3;
  inline bool has_timestamp() const;
  inline void clear_timestamp();
  static const int kTimeStampFieldNumber = 3;
  inline const ::std::string& timestamp() const;
  inline void set_timestamp(const ::std::string& value);
  inline void set_timestamp(const char* value);
  inline void set_timestamp(const char* value, size_t size);
  inline ::std::string* mutable_timestamp();
  inline ::std::string* release_timestamp();
  
  // @@protoc_insertion_point(class_scope:MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK)
 private:
  inline void set_has_statuscode();
  inline void clear_has_statuscode();
  inline void set_has_timestamp();
  inline void clear_has_timestamp();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO > singlenodesysinfo_;
  ::std::string* timestamp_;
  ::google::protobuf::int32 statuscode_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_MSG_5fDM_5fDC_5fDOMAIN_5fSYSINFO_5fGET_2eproto();
  friend void protobuf_AssignDesc_MSG_5fDM_5fDC_5fDOMAIN_5fSYSINFO_5fGET_2eproto();
  friend void protobuf_ShutdownFile_MSG_5fDM_5fDC_5fDOMAIN_5fSYSINFO_5fGET_2eproto();
  
  void InitAsDefaultInstance();
  static MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK* default_instance_;
};
// ===================================================================


// ===================================================================

// MSG_DM_DC_DOMAIN_SYSINFO_GET

// optional string timestamp = 1;
inline bool MSG_DM_DC_DOMAIN_SYSINFO_GET::has_timestamp() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MSG_DM_DC_DOMAIN_SYSINFO_GET::set_has_timestamp() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MSG_DM_DC_DOMAIN_SYSINFO_GET::clear_has_timestamp() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MSG_DM_DC_DOMAIN_SYSINFO_GET::clear_timestamp() {
  if (timestamp_ != &::google::protobuf::internal::kEmptyString) {
    timestamp_->clear();
  }
  clear_has_timestamp();
}
inline const ::std::string& MSG_DM_DC_DOMAIN_SYSINFO_GET::timestamp() const {
  return *timestamp_;
}
inline void MSG_DM_DC_DOMAIN_SYSINFO_GET::set_timestamp(const ::std::string& value) {
  set_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    timestamp_ = new ::std::string;
  }
  timestamp_->assign(value);
}
inline void MSG_DM_DC_DOMAIN_SYSINFO_GET::set_timestamp(const char* value) {
  set_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    timestamp_ = new ::std::string;
  }
  timestamp_->assign(value);
}
inline void MSG_DM_DC_DOMAIN_SYSINFO_GET::set_timestamp(const char* value, size_t size) {
  set_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    timestamp_ = new ::std::string;
  }
  timestamp_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MSG_DM_DC_DOMAIN_SYSINFO_GET::mutable_timestamp() {
  set_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    timestamp_ = new ::std::string;
  }
  return timestamp_;
}
inline ::std::string* MSG_DM_DC_DOMAIN_SYSINFO_GET::release_timestamp() {
  clear_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = timestamp_;
    timestamp_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO

// optional string nodeStatus = 1;
inline bool MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::has_nodestatus() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::set_has_nodestatus() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::clear_has_nodestatus() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::clear_nodestatus() {
  if (nodestatus_ != &::google::protobuf::internal::kEmptyString) {
    nodestatus_->clear();
  }
  clear_has_nodestatus();
}
inline const ::std::string& MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::nodestatus() const {
  return *nodestatus_;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::set_nodestatus(const ::std::string& value) {
  set_has_nodestatus();
  if (nodestatus_ == &::google::protobuf::internal::kEmptyString) {
    nodestatus_ = new ::std::string;
  }
  nodestatus_->assign(value);
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::set_nodestatus(const char* value) {
  set_has_nodestatus();
  if (nodestatus_ == &::google::protobuf::internal::kEmptyString) {
    nodestatus_ = new ::std::string;
  }
  nodestatus_->assign(value);
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::set_nodestatus(const char* value, size_t size) {
  set_has_nodestatus();
  if (nodestatus_ == &::google::protobuf::internal::kEmptyString) {
    nodestatus_ = new ::std::string;
  }
  nodestatus_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::mutable_nodestatus() {
  set_has_nodestatus();
  if (nodestatus_ == &::google::protobuf::internal::kEmptyString) {
    nodestatus_ = new ::std::string;
  }
  return nodestatus_;
}
inline ::std::string* MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::release_nodestatus() {
  clear_has_nodestatus();
  if (nodestatus_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = nodestatus_;
    nodestatus_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional uint32 core = 2;
inline bool MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::has_core() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::set_has_core() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::clear_has_core() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::clear_core() {
  core_ = 0u;
  clear_has_core();
}
inline ::google::protobuf::uint32 MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::core() const {
  return core_;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::set_core(::google::protobuf::uint32 value) {
  set_has_core();
  core_ = value;
}

// optional uint32 memSize = 3;
inline bool MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::has_memsize() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::set_has_memsize() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::clear_has_memsize() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::clear_memsize() {
  memsize_ = 0u;
  clear_has_memsize();
}
inline ::google::protobuf::uint32 MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::memsize() const {
  return memsize_;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO::set_memsize(::google::protobuf::uint32 value) {
  set_has_memsize();
  memsize_ = value;
}

// -------------------------------------------------------------------

// MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK

// optional int32 statusCode = 1;
inline bool MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::has_statuscode() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::set_has_statuscode() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::clear_has_statuscode() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::clear_statuscode() {
  statuscode_ = 0;
  clear_has_statuscode();
}
inline ::google::protobuf::int32 MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::statuscode() const {
  return statuscode_;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::set_statuscode(::google::protobuf::int32 value) {
  set_has_statuscode();
  statuscode_ = value;
}

// repeated .MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK.CS_SYS_INFO singleNodeSysInfo = 2;
inline int MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::singlenodesysinfo_size() const {
  return singlenodesysinfo_.size();
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::clear_singlenodesysinfo() {
  singlenodesysinfo_.Clear();
}
inline const ::MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO& MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::singlenodesysinfo(int index) const {
  return singlenodesysinfo_.Get(index);
}
inline ::MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO* MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::mutable_singlenodesysinfo(int index) {
  return singlenodesysinfo_.Mutable(index);
}
inline ::MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO* MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::add_singlenodesysinfo() {
  return singlenodesysinfo_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO >&
MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::singlenodesysinfo() const {
  return singlenodesysinfo_;
}
inline ::google::protobuf::RepeatedPtrField< ::MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK_CS_SYS_INFO >*
MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::mutable_singlenodesysinfo() {
  return &singlenodesysinfo_;
}

// optional string timeStamp = 3;
inline bool MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::has_timestamp() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::set_has_timestamp() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::clear_has_timestamp() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::clear_timestamp() {
  if (timestamp_ != &::google::protobuf::internal::kEmptyString) {
    timestamp_->clear();
  }
  clear_has_timestamp();
}
inline const ::std::string& MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::timestamp() const {
  return *timestamp_;
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::set_timestamp(const ::std::string& value) {
  set_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    timestamp_ = new ::std::string;
  }
  timestamp_->assign(value);
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::set_timestamp(const char* value) {
  set_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    timestamp_ = new ::std::string;
  }
  timestamp_->assign(value);
}
inline void MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::set_timestamp(const char* value, size_t size) {
  set_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    timestamp_ = new ::std::string;
  }
  timestamp_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::mutable_timestamp() {
  set_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    timestamp_ = new ::std::string;
  }
  return timestamp_;
}
inline ::std::string* MSG_DC_DM_DOMAIN_SYSINFO_GET_ACK::release_timestamp() {
  clear_has_timestamp();
  if (timestamp_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = timestamp_;
    timestamp_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_MSG_5fDM_5fDC_5fDOMAIN_5fSYSINFO_5fGET_2eproto__INCLUDED

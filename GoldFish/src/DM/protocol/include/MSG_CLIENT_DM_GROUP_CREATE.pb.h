// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MSG_CLIENT_DM_GROUP_CREATE.proto

#ifndef PROTOBUF_MSG_5fCLIENT_5fDM_5fGROUP_5fCREATE_2eproto__INCLUDED
#define PROTOBUF_MSG_5fCLIENT_5fDM_5fGROUP_5fCREATE_2eproto__INCLUDED

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
void  protobuf_AddDesc_MSG_5fCLIENT_5fDM_5fGROUP_5fCREATE_2eproto();
void protobuf_AssignDesc_MSG_5fCLIENT_5fDM_5fGROUP_5fCREATE_2eproto();
void protobuf_ShutdownFile_MSG_5fCLIENT_5fDM_5fGROUP_5fCREATE_2eproto();

class MSG_CLIENT_DM_GROUP_CREATE;
class MSG_DM_CLIENT_GROUP_CREATE_ACK;

// ===================================================================

class MSG_CLIENT_DM_GROUP_CREATE : public ::google::protobuf::Message {
 public:
  MSG_CLIENT_DM_GROUP_CREATE();
  virtual ~MSG_CLIENT_DM_GROUP_CREATE();
  
  MSG_CLIENT_DM_GROUP_CREATE(const MSG_CLIENT_DM_GROUP_CREATE& from);
  
  inline MSG_CLIENT_DM_GROUP_CREATE& operator=(const MSG_CLIENT_DM_GROUP_CREATE& from) {
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
  static const MSG_CLIENT_DM_GROUP_CREATE& default_instance();
  
  void Swap(MSG_CLIENT_DM_GROUP_CREATE* other);
  
  // implements Message ----------------------------------------------
  
  MSG_CLIENT_DM_GROUP_CREATE* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MSG_CLIENT_DM_GROUP_CREATE& from);
  void MergeFrom(const MSG_CLIENT_DM_GROUP_CREATE& from);
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
  
  // optional string token = 1;
  inline bool has_token() const;
  inline void clear_token();
  static const int kTokenFieldNumber = 1;
  inline const ::std::string& token() const;
  inline void set_token(const ::std::string& value);
  inline void set_token(const char* value);
  inline void set_token(const char* value, size_t size);
  inline ::std::string* mutable_token();
  inline ::std::string* release_token();
  
  // optional string groupName = 2;
  inline bool has_groupname() const;
  inline void clear_groupname();
  static const int kGroupNameFieldNumber = 2;
  inline const ::std::string& groupname() const;
  inline void set_groupname(const ::std::string& value);
  inline void set_groupname(const char* value);
  inline void set_groupname(const char* value, size_t size);
  inline ::std::string* mutable_groupname();
  inline ::std::string* release_groupname();
  
  // optional string belong2Domain = 3;
  inline bool has_belong2domain() const;
  inline void clear_belong2domain();
  static const int kBelong2DomainFieldNumber = 3;
  inline const ::std::string& belong2domain() const;
  inline void set_belong2domain(const ::std::string& value);
  inline void set_belong2domain(const char* value);
  inline void set_belong2domain(const char* value, size_t size);
  inline ::std::string* mutable_belong2domain();
  inline ::std::string* release_belong2domain();
  
  // optional string groupDescription = 4;
  inline bool has_groupdescription() const;
  inline void clear_groupdescription();
  static const int kGroupDescriptionFieldNumber = 4;
  inline const ::std::string& groupdescription() const;
  inline void set_groupdescription(const ::std::string& value);
  inline void set_groupdescription(const char* value);
  inline void set_groupdescription(const char* value, size_t size);
  inline ::std::string* mutable_groupdescription();
  inline ::std::string* release_groupdescription();
  
  // @@protoc_insertion_point(class_scope:MSG_CLIENT_DM_GROUP_CREATE)
 private:
  inline void set_has_token();
  inline void clear_has_token();
  inline void set_has_groupname();
  inline void clear_has_groupname();
  inline void set_has_belong2domain();
  inline void clear_has_belong2domain();
  inline void set_has_groupdescription();
  inline void clear_has_groupdescription();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* token_;
  ::std::string* groupname_;
  ::std::string* belong2domain_;
  ::std::string* groupdescription_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  friend void  protobuf_AddDesc_MSG_5fCLIENT_5fDM_5fGROUP_5fCREATE_2eproto();
  friend void protobuf_AssignDesc_MSG_5fCLIENT_5fDM_5fGROUP_5fCREATE_2eproto();
  friend void protobuf_ShutdownFile_MSG_5fCLIENT_5fDM_5fGROUP_5fCREATE_2eproto();
  
  void InitAsDefaultInstance();
  static MSG_CLIENT_DM_GROUP_CREATE* default_instance_;
};
// -------------------------------------------------------------------

class MSG_DM_CLIENT_GROUP_CREATE_ACK : public ::google::protobuf::Message {
 public:
  MSG_DM_CLIENT_GROUP_CREATE_ACK();
  virtual ~MSG_DM_CLIENT_GROUP_CREATE_ACK();
  
  MSG_DM_CLIENT_GROUP_CREATE_ACK(const MSG_DM_CLIENT_GROUP_CREATE_ACK& from);
  
  inline MSG_DM_CLIENT_GROUP_CREATE_ACK& operator=(const MSG_DM_CLIENT_GROUP_CREATE_ACK& from) {
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
  static const MSG_DM_CLIENT_GROUP_CREATE_ACK& default_instance();
  
  void Swap(MSG_DM_CLIENT_GROUP_CREATE_ACK* other);
  
  // implements Message ----------------------------------------------
  
  MSG_DM_CLIENT_GROUP_CREATE_ACK* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MSG_DM_CLIENT_GROUP_CREATE_ACK& from);
  void MergeFrom(const MSG_DM_CLIENT_GROUP_CREATE_ACK& from);
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
  
  // optional int32 statusCode = 1;
  inline bool has_statuscode() const;
  inline void clear_statuscode();
  static const int kStatusCodeFieldNumber = 1;
  inline ::google::protobuf::int32 statuscode() const;
  inline void set_statuscode(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:MSG_DM_CLIENT_GROUP_CREATE_ACK)
 private:
  inline void set_has_statuscode();
  inline void clear_has_statuscode();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 statuscode_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_MSG_5fCLIENT_5fDM_5fGROUP_5fCREATE_2eproto();
  friend void protobuf_AssignDesc_MSG_5fCLIENT_5fDM_5fGROUP_5fCREATE_2eproto();
  friend void protobuf_ShutdownFile_MSG_5fCLIENT_5fDM_5fGROUP_5fCREATE_2eproto();
  
  void InitAsDefaultInstance();
  static MSG_DM_CLIENT_GROUP_CREATE_ACK* default_instance_;
};
// ===================================================================


// ===================================================================

// MSG_CLIENT_DM_GROUP_CREATE

// optional string token = 1;
inline bool MSG_CLIENT_DM_GROUP_CREATE::has_token() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MSG_CLIENT_DM_GROUP_CREATE::set_has_token() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MSG_CLIENT_DM_GROUP_CREATE::clear_has_token() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MSG_CLIENT_DM_GROUP_CREATE::clear_token() {
  if (token_ != &::google::protobuf::internal::kEmptyString) {
    token_->clear();
  }
  clear_has_token();
}
inline const ::std::string& MSG_CLIENT_DM_GROUP_CREATE::token() const {
  return *token_;
}
inline void MSG_CLIENT_DM_GROUP_CREATE::set_token(const ::std::string& value) {
  set_has_token();
  if (token_ == &::google::protobuf::internal::kEmptyString) {
    token_ = new ::std::string;
  }
  token_->assign(value);
}
inline void MSG_CLIENT_DM_GROUP_CREATE::set_token(const char* value) {
  set_has_token();
  if (token_ == &::google::protobuf::internal::kEmptyString) {
    token_ = new ::std::string;
  }
  token_->assign(value);
}
inline void MSG_CLIENT_DM_GROUP_CREATE::set_token(const char* value, size_t size) {
  set_has_token();
  if (token_ == &::google::protobuf::internal::kEmptyString) {
    token_ = new ::std::string;
  }
  token_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MSG_CLIENT_DM_GROUP_CREATE::mutable_token() {
  set_has_token();
  if (token_ == &::google::protobuf::internal::kEmptyString) {
    token_ = new ::std::string;
  }
  return token_;
}
inline ::std::string* MSG_CLIENT_DM_GROUP_CREATE::release_token() {
  clear_has_token();
  if (token_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = token_;
    token_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional string groupName = 2;
inline bool MSG_CLIENT_DM_GROUP_CREATE::has_groupname() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MSG_CLIENT_DM_GROUP_CREATE::set_has_groupname() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MSG_CLIENT_DM_GROUP_CREATE::clear_has_groupname() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MSG_CLIENT_DM_GROUP_CREATE::clear_groupname() {
  if (groupname_ != &::google::protobuf::internal::kEmptyString) {
    groupname_->clear();
  }
  clear_has_groupname();
}
inline const ::std::string& MSG_CLIENT_DM_GROUP_CREATE::groupname() const {
  return *groupname_;
}
inline void MSG_CLIENT_DM_GROUP_CREATE::set_groupname(const ::std::string& value) {
  set_has_groupname();
  if (groupname_ == &::google::protobuf::internal::kEmptyString) {
    groupname_ = new ::std::string;
  }
  groupname_->assign(value);
}
inline void MSG_CLIENT_DM_GROUP_CREATE::set_groupname(const char* value) {
  set_has_groupname();
  if (groupname_ == &::google::protobuf::internal::kEmptyString) {
    groupname_ = new ::std::string;
  }
  groupname_->assign(value);
}
inline void MSG_CLIENT_DM_GROUP_CREATE::set_groupname(const char* value, size_t size) {
  set_has_groupname();
  if (groupname_ == &::google::protobuf::internal::kEmptyString) {
    groupname_ = new ::std::string;
  }
  groupname_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MSG_CLIENT_DM_GROUP_CREATE::mutable_groupname() {
  set_has_groupname();
  if (groupname_ == &::google::protobuf::internal::kEmptyString) {
    groupname_ = new ::std::string;
  }
  return groupname_;
}
inline ::std::string* MSG_CLIENT_DM_GROUP_CREATE::release_groupname() {
  clear_has_groupname();
  if (groupname_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = groupname_;
    groupname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional string belong2Domain = 3;
inline bool MSG_CLIENT_DM_GROUP_CREATE::has_belong2domain() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MSG_CLIENT_DM_GROUP_CREATE::set_has_belong2domain() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MSG_CLIENT_DM_GROUP_CREATE::clear_has_belong2domain() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MSG_CLIENT_DM_GROUP_CREATE::clear_belong2domain() {
  if (belong2domain_ != &::google::protobuf::internal::kEmptyString) {
    belong2domain_->clear();
  }
  clear_has_belong2domain();
}
inline const ::std::string& MSG_CLIENT_DM_GROUP_CREATE::belong2domain() const {
  return *belong2domain_;
}
inline void MSG_CLIENT_DM_GROUP_CREATE::set_belong2domain(const ::std::string& value) {
  set_has_belong2domain();
  if (belong2domain_ == &::google::protobuf::internal::kEmptyString) {
    belong2domain_ = new ::std::string;
  }
  belong2domain_->assign(value);
}
inline void MSG_CLIENT_DM_GROUP_CREATE::set_belong2domain(const char* value) {
  set_has_belong2domain();
  if (belong2domain_ == &::google::protobuf::internal::kEmptyString) {
    belong2domain_ = new ::std::string;
  }
  belong2domain_->assign(value);
}
inline void MSG_CLIENT_DM_GROUP_CREATE::set_belong2domain(const char* value, size_t size) {
  set_has_belong2domain();
  if (belong2domain_ == &::google::protobuf::internal::kEmptyString) {
    belong2domain_ = new ::std::string;
  }
  belong2domain_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MSG_CLIENT_DM_GROUP_CREATE::mutable_belong2domain() {
  set_has_belong2domain();
  if (belong2domain_ == &::google::protobuf::internal::kEmptyString) {
    belong2domain_ = new ::std::string;
  }
  return belong2domain_;
}
inline ::std::string* MSG_CLIENT_DM_GROUP_CREATE::release_belong2domain() {
  clear_has_belong2domain();
  if (belong2domain_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = belong2domain_;
    belong2domain_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional string groupDescription = 4;
inline bool MSG_CLIENT_DM_GROUP_CREATE::has_groupdescription() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void MSG_CLIENT_DM_GROUP_CREATE::set_has_groupdescription() {
  _has_bits_[0] |= 0x00000008u;
}
inline void MSG_CLIENT_DM_GROUP_CREATE::clear_has_groupdescription() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void MSG_CLIENT_DM_GROUP_CREATE::clear_groupdescription() {
  if (groupdescription_ != &::google::protobuf::internal::kEmptyString) {
    groupdescription_->clear();
  }
  clear_has_groupdescription();
}
inline const ::std::string& MSG_CLIENT_DM_GROUP_CREATE::groupdescription() const {
  return *groupdescription_;
}
inline void MSG_CLIENT_DM_GROUP_CREATE::set_groupdescription(const ::std::string& value) {
  set_has_groupdescription();
  if (groupdescription_ == &::google::protobuf::internal::kEmptyString) {
    groupdescription_ = new ::std::string;
  }
  groupdescription_->assign(value);
}
inline void MSG_CLIENT_DM_GROUP_CREATE::set_groupdescription(const char* value) {
  set_has_groupdescription();
  if (groupdescription_ == &::google::protobuf::internal::kEmptyString) {
    groupdescription_ = new ::std::string;
  }
  groupdescription_->assign(value);
}
inline void MSG_CLIENT_DM_GROUP_CREATE::set_groupdescription(const char* value, size_t size) {
  set_has_groupdescription();
  if (groupdescription_ == &::google::protobuf::internal::kEmptyString) {
    groupdescription_ = new ::std::string;
  }
  groupdescription_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MSG_CLIENT_DM_GROUP_CREATE::mutable_groupdescription() {
  set_has_groupdescription();
  if (groupdescription_ == &::google::protobuf::internal::kEmptyString) {
    groupdescription_ = new ::std::string;
  }
  return groupdescription_;
}
inline ::std::string* MSG_CLIENT_DM_GROUP_CREATE::release_groupdescription() {
  clear_has_groupdescription();
  if (groupdescription_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = groupdescription_;
    groupdescription_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// MSG_DM_CLIENT_GROUP_CREATE_ACK

// optional int32 statusCode = 1;
inline bool MSG_DM_CLIENT_GROUP_CREATE_ACK::has_statuscode() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MSG_DM_CLIENT_GROUP_CREATE_ACK::set_has_statuscode() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MSG_DM_CLIENT_GROUP_CREATE_ACK::clear_has_statuscode() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MSG_DM_CLIENT_GROUP_CREATE_ACK::clear_statuscode() {
  statuscode_ = 0;
  clear_has_statuscode();
}
inline ::google::protobuf::int32 MSG_DM_CLIENT_GROUP_CREATE_ACK::statuscode() const {
  return statuscode_;
}
inline void MSG_DM_CLIENT_GROUP_CREATE_ACK::set_statuscode(::google::protobuf::int32 value) {
  set_has_statuscode();
  statuscode_ = value;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_MSG_5fCLIENT_5fDM_5fGROUP_5fCREATE_2eproto__INCLUDED

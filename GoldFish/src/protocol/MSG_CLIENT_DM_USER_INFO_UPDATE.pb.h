// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MSG_CLIENT_DM_USER_INFO_UPDATE.proto

#ifndef PROTOBUF_MSG_5fCLIENT_5fDM_5fUSER_5fINFO_5fUPDATE_2eproto__INCLUDED
#define PROTOBUF_MSG_5fCLIENT_5fDM_5fUSER_5fINFO_5fUPDATE_2eproto__INCLUDED

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
void  protobuf_AddDesc_MSG_5fCLIENT_5fDM_5fUSER_5fINFO_5fUPDATE_2eproto();
void protobuf_AssignDesc_MSG_5fCLIENT_5fDM_5fUSER_5fINFO_5fUPDATE_2eproto();
void protobuf_ShutdownFile_MSG_5fCLIENT_5fDM_5fUSER_5fINFO_5fUPDATE_2eproto();

class MSG_CLIENT_DM_USER_INFO_UPDATE;
class MSG_DM_CLIENT_USER_INFO_UPDATE_ACK;

// ===================================================================

class MSG_CLIENT_DM_USER_INFO_UPDATE : public ::google::protobuf::Message {
 public:
  MSG_CLIENT_DM_USER_INFO_UPDATE();
  virtual ~MSG_CLIENT_DM_USER_INFO_UPDATE();
  
  MSG_CLIENT_DM_USER_INFO_UPDATE(const MSG_CLIENT_DM_USER_INFO_UPDATE& from);
  
  inline MSG_CLIENT_DM_USER_INFO_UPDATE& operator=(const MSG_CLIENT_DM_USER_INFO_UPDATE& from) {
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
  static const MSG_CLIENT_DM_USER_INFO_UPDATE& default_instance();
  
  void Swap(MSG_CLIENT_DM_USER_INFO_UPDATE* other);
  
  // implements Message ----------------------------------------------
  
  MSG_CLIENT_DM_USER_INFO_UPDATE* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MSG_CLIENT_DM_USER_INFO_UPDATE& from);
  void MergeFrom(const MSG_CLIENT_DM_USER_INFO_UPDATE& from);
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
  
  // optional string password = 2;
  inline bool has_password() const;
  inline void clear_password();
  static const int kPasswordFieldNumber = 2;
  inline const ::std::string& password() const;
  inline void set_password(const ::std::string& value);
  inline void set_password(const char* value);
  inline void set_password(const char* value, size_t size);
  inline ::std::string* mutable_password();
  inline ::std::string* release_password();
  
  // @@protoc_insertion_point(class_scope:MSG_CLIENT_DM_USER_INFO_UPDATE)
 private:
  inline void set_has_token();
  inline void clear_has_token();
  inline void set_has_password();
  inline void clear_has_password();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* token_;
  ::std::string* password_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_MSG_5fCLIENT_5fDM_5fUSER_5fINFO_5fUPDATE_2eproto();
  friend void protobuf_AssignDesc_MSG_5fCLIENT_5fDM_5fUSER_5fINFO_5fUPDATE_2eproto();
  friend void protobuf_ShutdownFile_MSG_5fCLIENT_5fDM_5fUSER_5fINFO_5fUPDATE_2eproto();
  
  void InitAsDefaultInstance();
  static MSG_CLIENT_DM_USER_INFO_UPDATE* default_instance_;
};
// -------------------------------------------------------------------

class MSG_DM_CLIENT_USER_INFO_UPDATE_ACK : public ::google::protobuf::Message {
 public:
  MSG_DM_CLIENT_USER_INFO_UPDATE_ACK();
  virtual ~MSG_DM_CLIENT_USER_INFO_UPDATE_ACK();
  
  MSG_DM_CLIENT_USER_INFO_UPDATE_ACK(const MSG_DM_CLIENT_USER_INFO_UPDATE_ACK& from);
  
  inline MSG_DM_CLIENT_USER_INFO_UPDATE_ACK& operator=(const MSG_DM_CLIENT_USER_INFO_UPDATE_ACK& from) {
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
  static const MSG_DM_CLIENT_USER_INFO_UPDATE_ACK& default_instance();
  
  void Swap(MSG_DM_CLIENT_USER_INFO_UPDATE_ACK* other);
  
  // implements Message ----------------------------------------------
  
  MSG_DM_CLIENT_USER_INFO_UPDATE_ACK* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MSG_DM_CLIENT_USER_INFO_UPDATE_ACK& from);
  void MergeFrom(const MSG_DM_CLIENT_USER_INFO_UPDATE_ACK& from);
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
  
  // @@protoc_insertion_point(class_scope:MSG_DM_CLIENT_USER_INFO_UPDATE_ACK)
 private:
  inline void set_has_statuscode();
  inline void clear_has_statuscode();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 statuscode_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_MSG_5fCLIENT_5fDM_5fUSER_5fINFO_5fUPDATE_2eproto();
  friend void protobuf_AssignDesc_MSG_5fCLIENT_5fDM_5fUSER_5fINFO_5fUPDATE_2eproto();
  friend void protobuf_ShutdownFile_MSG_5fCLIENT_5fDM_5fUSER_5fINFO_5fUPDATE_2eproto();
  
  void InitAsDefaultInstance();
  static MSG_DM_CLIENT_USER_INFO_UPDATE_ACK* default_instance_;
};
// ===================================================================


// ===================================================================

// MSG_CLIENT_DM_USER_INFO_UPDATE

// optional string token = 1;
inline bool MSG_CLIENT_DM_USER_INFO_UPDATE::has_token() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MSG_CLIENT_DM_USER_INFO_UPDATE::set_has_token() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MSG_CLIENT_DM_USER_INFO_UPDATE::clear_has_token() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MSG_CLIENT_DM_USER_INFO_UPDATE::clear_token() {
  if (token_ != &::google::protobuf::internal::kEmptyString) {
    token_->clear();
  }
  clear_has_token();
}
inline const ::std::string& MSG_CLIENT_DM_USER_INFO_UPDATE::token() const {
  return *token_;
}
inline void MSG_CLIENT_DM_USER_INFO_UPDATE::set_token(const ::std::string& value) {
  set_has_token();
  if (token_ == &::google::protobuf::internal::kEmptyString) {
    token_ = new ::std::string;
  }
  token_->assign(value);
}
inline void MSG_CLIENT_DM_USER_INFO_UPDATE::set_token(const char* value) {
  set_has_token();
  if (token_ == &::google::protobuf::internal::kEmptyString) {
    token_ = new ::std::string;
  }
  token_->assign(value);
}
inline void MSG_CLIENT_DM_USER_INFO_UPDATE::set_token(const char* value, size_t size) {
  set_has_token();
  if (token_ == &::google::protobuf::internal::kEmptyString) {
    token_ = new ::std::string;
  }
  token_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MSG_CLIENT_DM_USER_INFO_UPDATE::mutable_token() {
  set_has_token();
  if (token_ == &::google::protobuf::internal::kEmptyString) {
    token_ = new ::std::string;
  }
  return token_;
}
inline ::std::string* MSG_CLIENT_DM_USER_INFO_UPDATE::release_token() {
  clear_has_token();
  if (token_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = token_;
    token_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// optional string password = 2;
inline bool MSG_CLIENT_DM_USER_INFO_UPDATE::has_password() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MSG_CLIENT_DM_USER_INFO_UPDATE::set_has_password() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MSG_CLIENT_DM_USER_INFO_UPDATE::clear_has_password() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MSG_CLIENT_DM_USER_INFO_UPDATE::clear_password() {
  if (password_ != &::google::protobuf::internal::kEmptyString) {
    password_->clear();
  }
  clear_has_password();
}
inline const ::std::string& MSG_CLIENT_DM_USER_INFO_UPDATE::password() const {
  return *password_;
}
inline void MSG_CLIENT_DM_USER_INFO_UPDATE::set_password(const ::std::string& value) {
  set_has_password();
  if (password_ == &::google::protobuf::internal::kEmptyString) {
    password_ = new ::std::string;
  }
  password_->assign(value);
}
inline void MSG_CLIENT_DM_USER_INFO_UPDATE::set_password(const char* value) {
  set_has_password();
  if (password_ == &::google::protobuf::internal::kEmptyString) {
    password_ = new ::std::string;
  }
  password_->assign(value);
}
inline void MSG_CLIENT_DM_USER_INFO_UPDATE::set_password(const char* value, size_t size) {
  set_has_password();
  if (password_ == &::google::protobuf::internal::kEmptyString) {
    password_ = new ::std::string;
  }
  password_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MSG_CLIENT_DM_USER_INFO_UPDATE::mutable_password() {
  set_has_password();
  if (password_ == &::google::protobuf::internal::kEmptyString) {
    password_ = new ::std::string;
  }
  return password_;
}
inline ::std::string* MSG_CLIENT_DM_USER_INFO_UPDATE::release_password() {
  clear_has_password();
  if (password_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = password_;
    password_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// MSG_DM_CLIENT_USER_INFO_UPDATE_ACK

// optional int32 statusCode = 1;
inline bool MSG_DM_CLIENT_USER_INFO_UPDATE_ACK::has_statuscode() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MSG_DM_CLIENT_USER_INFO_UPDATE_ACK::set_has_statuscode() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MSG_DM_CLIENT_USER_INFO_UPDATE_ACK::clear_has_statuscode() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MSG_DM_CLIENT_USER_INFO_UPDATE_ACK::clear_statuscode() {
  statuscode_ = 0;
  clear_has_statuscode();
}
inline ::google::protobuf::int32 MSG_DM_CLIENT_USER_INFO_UPDATE_ACK::statuscode() const {
  return statuscode_;
}
inline void MSG_DM_CLIENT_USER_INFO_UPDATE_ACK::set_statuscode(::google::protobuf::int32 value) {
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

#endif  // PROTOBUF_MSG_5fCLIENT_5fDM_5fUSER_5fINFO_5fUPDATE_2eproto__INCLUDED

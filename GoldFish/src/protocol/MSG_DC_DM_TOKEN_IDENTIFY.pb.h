// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MSG_DC_DM_TOKEN_IDENTIFY.proto

#ifndef PROTOBUF_MSG_5fDC_5fDM_5fTOKEN_5fIDENTIFY_2eproto__INCLUDED
#define PROTOBUF_MSG_5fDC_5fDM_5fTOKEN_5fIDENTIFY_2eproto__INCLUDED

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
void  protobuf_AddDesc_MSG_5fDC_5fDM_5fTOKEN_5fIDENTIFY_2eproto();
void protobuf_AssignDesc_MSG_5fDC_5fDM_5fTOKEN_5fIDENTIFY_2eproto();
void protobuf_ShutdownFile_MSG_5fDC_5fDM_5fTOKEN_5fIDENTIFY_2eproto();

class MSG_DC_DM_TOKEN_IDENTIFY;
class MSG_DM_DC_TOKEN_IDENTIFY_ACK;

// ===================================================================

class MSG_DC_DM_TOKEN_IDENTIFY : public ::google::protobuf::Message {
 public:
  MSG_DC_DM_TOKEN_IDENTIFY();
  virtual ~MSG_DC_DM_TOKEN_IDENTIFY();
  
  MSG_DC_DM_TOKEN_IDENTIFY(const MSG_DC_DM_TOKEN_IDENTIFY& from);
  
  inline MSG_DC_DM_TOKEN_IDENTIFY& operator=(const MSG_DC_DM_TOKEN_IDENTIFY& from) {
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
  static const MSG_DC_DM_TOKEN_IDENTIFY& default_instance();
  
  void Swap(MSG_DC_DM_TOKEN_IDENTIFY* other);
  
  // implements Message ----------------------------------------------
  
  MSG_DC_DM_TOKEN_IDENTIFY* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MSG_DC_DM_TOKEN_IDENTIFY& from);
  void MergeFrom(const MSG_DC_DM_TOKEN_IDENTIFY& from);
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
  
  // optional string encryptedToken = 1;
  inline bool has_encryptedtoken() const;
  inline void clear_encryptedtoken();
  static const int kEncryptedTokenFieldNumber = 1;
  inline const ::std::string& encryptedtoken() const;
  inline void set_encryptedtoken(const ::std::string& value);
  inline void set_encryptedtoken(const char* value);
  inline void set_encryptedtoken(const char* value, size_t size);
  inline ::std::string* mutable_encryptedtoken();
  inline ::std::string* release_encryptedtoken();
  
  // @@protoc_insertion_point(class_scope:MSG_DC_DM_TOKEN_IDENTIFY)
 private:
  inline void set_has_encryptedtoken();
  inline void clear_has_encryptedtoken();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* encryptedtoken_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_MSG_5fDC_5fDM_5fTOKEN_5fIDENTIFY_2eproto();
  friend void protobuf_AssignDesc_MSG_5fDC_5fDM_5fTOKEN_5fIDENTIFY_2eproto();
  friend void protobuf_ShutdownFile_MSG_5fDC_5fDM_5fTOKEN_5fIDENTIFY_2eproto();
  
  void InitAsDefaultInstance();
  static MSG_DC_DM_TOKEN_IDENTIFY* default_instance_;
};
// -------------------------------------------------------------------

class MSG_DM_DC_TOKEN_IDENTIFY_ACK : public ::google::protobuf::Message {
 public:
  MSG_DM_DC_TOKEN_IDENTIFY_ACK();
  virtual ~MSG_DM_DC_TOKEN_IDENTIFY_ACK();
  
  MSG_DM_DC_TOKEN_IDENTIFY_ACK(const MSG_DM_DC_TOKEN_IDENTIFY_ACK& from);
  
  inline MSG_DM_DC_TOKEN_IDENTIFY_ACK& operator=(const MSG_DM_DC_TOKEN_IDENTIFY_ACK& from) {
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
  static const MSG_DM_DC_TOKEN_IDENTIFY_ACK& default_instance();
  
  void Swap(MSG_DM_DC_TOKEN_IDENTIFY_ACK* other);
  
  // implements Message ----------------------------------------------
  
  MSG_DM_DC_TOKEN_IDENTIFY_ACK* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MSG_DM_DC_TOKEN_IDENTIFY_ACK& from);
  void MergeFrom(const MSG_DM_DC_TOKEN_IDENTIFY_ACK& from);
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
  
  // optional string rawToken = 2;
  inline bool has_rawtoken() const;
  inline void clear_rawtoken();
  static const int kRawTokenFieldNumber = 2;
  inline const ::std::string& rawtoken() const;
  inline void set_rawtoken(const ::std::string& value);
  inline void set_rawtoken(const char* value);
  inline void set_rawtoken(const char* value, size_t size);
  inline ::std::string* mutable_rawtoken();
  inline ::std::string* release_rawtoken();
  
  // @@protoc_insertion_point(class_scope:MSG_DM_DC_TOKEN_IDENTIFY_ACK)
 private:
  inline void set_has_statuscode();
  inline void clear_has_statuscode();
  inline void set_has_rawtoken();
  inline void clear_has_rawtoken();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* rawtoken_;
  ::google::protobuf::int32 statuscode_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_MSG_5fDC_5fDM_5fTOKEN_5fIDENTIFY_2eproto();
  friend void protobuf_AssignDesc_MSG_5fDC_5fDM_5fTOKEN_5fIDENTIFY_2eproto();
  friend void protobuf_ShutdownFile_MSG_5fDC_5fDM_5fTOKEN_5fIDENTIFY_2eproto();
  
  void InitAsDefaultInstance();
  static MSG_DM_DC_TOKEN_IDENTIFY_ACK* default_instance_;
};
// ===================================================================


// ===================================================================

// MSG_DC_DM_TOKEN_IDENTIFY

// optional string encryptedToken = 1;
inline bool MSG_DC_DM_TOKEN_IDENTIFY::has_encryptedtoken() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MSG_DC_DM_TOKEN_IDENTIFY::set_has_encryptedtoken() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MSG_DC_DM_TOKEN_IDENTIFY::clear_has_encryptedtoken() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MSG_DC_DM_TOKEN_IDENTIFY::clear_encryptedtoken() {
  if (encryptedtoken_ != &::google::protobuf::internal::kEmptyString) {
    encryptedtoken_->clear();
  }
  clear_has_encryptedtoken();
}
inline const ::std::string& MSG_DC_DM_TOKEN_IDENTIFY::encryptedtoken() const {
  return *encryptedtoken_;
}
inline void MSG_DC_DM_TOKEN_IDENTIFY::set_encryptedtoken(const ::std::string& value) {
  set_has_encryptedtoken();
  if (encryptedtoken_ == &::google::protobuf::internal::kEmptyString) {
    encryptedtoken_ = new ::std::string;
  }
  encryptedtoken_->assign(value);
}
inline void MSG_DC_DM_TOKEN_IDENTIFY::set_encryptedtoken(const char* value) {
  set_has_encryptedtoken();
  if (encryptedtoken_ == &::google::protobuf::internal::kEmptyString) {
    encryptedtoken_ = new ::std::string;
  }
  encryptedtoken_->assign(value);
}
inline void MSG_DC_DM_TOKEN_IDENTIFY::set_encryptedtoken(const char* value, size_t size) {
  set_has_encryptedtoken();
  if (encryptedtoken_ == &::google::protobuf::internal::kEmptyString) {
    encryptedtoken_ = new ::std::string;
  }
  encryptedtoken_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MSG_DC_DM_TOKEN_IDENTIFY::mutable_encryptedtoken() {
  set_has_encryptedtoken();
  if (encryptedtoken_ == &::google::protobuf::internal::kEmptyString) {
    encryptedtoken_ = new ::std::string;
  }
  return encryptedtoken_;
}
inline ::std::string* MSG_DC_DM_TOKEN_IDENTIFY::release_encryptedtoken() {
  clear_has_encryptedtoken();
  if (encryptedtoken_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = encryptedtoken_;
    encryptedtoken_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// -------------------------------------------------------------------

// MSG_DM_DC_TOKEN_IDENTIFY_ACK

// optional int32 statusCode = 1;
inline bool MSG_DM_DC_TOKEN_IDENTIFY_ACK::has_statuscode() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MSG_DM_DC_TOKEN_IDENTIFY_ACK::set_has_statuscode() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MSG_DM_DC_TOKEN_IDENTIFY_ACK::clear_has_statuscode() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MSG_DM_DC_TOKEN_IDENTIFY_ACK::clear_statuscode() {
  statuscode_ = 0;
  clear_has_statuscode();
}
inline ::google::protobuf::int32 MSG_DM_DC_TOKEN_IDENTIFY_ACK::statuscode() const {
  return statuscode_;
}
inline void MSG_DM_DC_TOKEN_IDENTIFY_ACK::set_statuscode(::google::protobuf::int32 value) {
  set_has_statuscode();
  statuscode_ = value;
}

// optional string rawToken = 2;
inline bool MSG_DM_DC_TOKEN_IDENTIFY_ACK::has_rawtoken() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MSG_DM_DC_TOKEN_IDENTIFY_ACK::set_has_rawtoken() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MSG_DM_DC_TOKEN_IDENTIFY_ACK::clear_has_rawtoken() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MSG_DM_DC_TOKEN_IDENTIFY_ACK::clear_rawtoken() {
  if (rawtoken_ != &::google::protobuf::internal::kEmptyString) {
    rawtoken_->clear();
  }
  clear_has_rawtoken();
}
inline const ::std::string& MSG_DM_DC_TOKEN_IDENTIFY_ACK::rawtoken() const {
  return *rawtoken_;
}
inline void MSG_DM_DC_TOKEN_IDENTIFY_ACK::set_rawtoken(const ::std::string& value) {
  set_has_rawtoken();
  if (rawtoken_ == &::google::protobuf::internal::kEmptyString) {
    rawtoken_ = new ::std::string;
  }
  rawtoken_->assign(value);
}
inline void MSG_DM_DC_TOKEN_IDENTIFY_ACK::set_rawtoken(const char* value) {
  set_has_rawtoken();
  if (rawtoken_ == &::google::protobuf::internal::kEmptyString) {
    rawtoken_ = new ::std::string;
  }
  rawtoken_->assign(value);
}
inline void MSG_DM_DC_TOKEN_IDENTIFY_ACK::set_rawtoken(const char* value, size_t size) {
  set_has_rawtoken();
  if (rawtoken_ == &::google::protobuf::internal::kEmptyString) {
    rawtoken_ = new ::std::string;
  }
  rawtoken_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* MSG_DM_DC_TOKEN_IDENTIFY_ACK::mutable_rawtoken() {
  set_has_rawtoken();
  if (rawtoken_ == &::google::protobuf::internal::kEmptyString) {
    rawtoken_ = new ::std::string;
  }
  return rawtoken_;
}
inline ::std::string* MSG_DM_DC_TOKEN_IDENTIFY_ACK::release_rawtoken() {
  clear_has_rawtoken();
  if (rawtoken_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = rawtoken_;
    rawtoken_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
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

#endif  // PROTOBUF_MSG_5fDC_5fDM_5fTOKEN_5fIDENTIFY_2eproto__INCLUDED
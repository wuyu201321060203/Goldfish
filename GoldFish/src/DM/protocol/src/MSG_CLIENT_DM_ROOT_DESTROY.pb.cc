// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "MSG_CLIENT_DM_ROOT_DESTROY.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* MSG_CLIENT_DM_ROOT_DESTORY_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MSG_CLIENT_DM_ROOT_DESTORY_reflection_ = NULL;
const ::google::protobuf::Descriptor* MSG_DM_CLIENT_ROOT_DESTORY_ACK_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MSG_DM_CLIENT_ROOT_DESTORY_ACK_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_MSG_5fCLIENT_5fDM_5fROOT_5fDESTROY_2eproto() {
  protobuf_AddDesc_MSG_5fCLIENT_5fDM_5fROOT_5fDESTROY_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "MSG_CLIENT_DM_ROOT_DESTROY.proto");
  GOOGLE_CHECK(file != NULL);
  MSG_CLIENT_DM_ROOT_DESTORY_descriptor_ = file->message_type(0);
  static const int MSG_CLIENT_DM_ROOT_DESTORY_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSG_CLIENT_DM_ROOT_DESTORY, token_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSG_CLIENT_DM_ROOT_DESTORY, username_),
  };
  MSG_CLIENT_DM_ROOT_DESTORY_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      MSG_CLIENT_DM_ROOT_DESTORY_descriptor_,
      MSG_CLIENT_DM_ROOT_DESTORY::default_instance_,
      MSG_CLIENT_DM_ROOT_DESTORY_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSG_CLIENT_DM_ROOT_DESTORY, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSG_CLIENT_DM_ROOT_DESTORY, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(MSG_CLIENT_DM_ROOT_DESTORY));
  MSG_DM_CLIENT_ROOT_DESTORY_ACK_descriptor_ = file->message_type(1);
  static const int MSG_DM_CLIENT_ROOT_DESTORY_ACK_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSG_DM_CLIENT_ROOT_DESTORY_ACK, statuscode_),
  };
  MSG_DM_CLIENT_ROOT_DESTORY_ACK_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      MSG_DM_CLIENT_ROOT_DESTORY_ACK_descriptor_,
      MSG_DM_CLIENT_ROOT_DESTORY_ACK::default_instance_,
      MSG_DM_CLIENT_ROOT_DESTORY_ACK_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSG_DM_CLIENT_ROOT_DESTORY_ACK, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSG_DM_CLIENT_ROOT_DESTORY_ACK, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(MSG_DM_CLIENT_ROOT_DESTORY_ACK));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_MSG_5fCLIENT_5fDM_5fROOT_5fDESTROY_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    MSG_CLIENT_DM_ROOT_DESTORY_descriptor_, &MSG_CLIENT_DM_ROOT_DESTORY::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    MSG_DM_CLIENT_ROOT_DESTORY_ACK_descriptor_, &MSG_DM_CLIENT_ROOT_DESTORY_ACK::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_MSG_5fCLIENT_5fDM_5fROOT_5fDESTROY_2eproto() {
  delete MSG_CLIENT_DM_ROOT_DESTORY::default_instance_;
  delete MSG_CLIENT_DM_ROOT_DESTORY_reflection_;
  delete MSG_DM_CLIENT_ROOT_DESTORY_ACK::default_instance_;
  delete MSG_DM_CLIENT_ROOT_DESTORY_ACK_reflection_;
}

void protobuf_AddDesc_MSG_5fCLIENT_5fDM_5fROOT_5fDESTROY_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n MSG_CLIENT_DM_ROOT_DESTROY.proto\"=\n\032MS"
    "G_CLIENT_DM_ROOT_DESTORY\022\r\n\005token\030\001 \001(\t\022"
    "\020\n\010userName\030\002 \001(\t\"4\n\036MSG_DM_CLIENT_ROOT_"
    "DESTORY_ACK\022\022\n\nstatusCode\030\001 \001(\005", 151);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "MSG_CLIENT_DM_ROOT_DESTROY.proto", &protobuf_RegisterTypes);
  MSG_CLIENT_DM_ROOT_DESTORY::default_instance_ = new MSG_CLIENT_DM_ROOT_DESTORY();
  MSG_DM_CLIENT_ROOT_DESTORY_ACK::default_instance_ = new MSG_DM_CLIENT_ROOT_DESTORY_ACK();
  MSG_CLIENT_DM_ROOT_DESTORY::default_instance_->InitAsDefaultInstance();
  MSG_DM_CLIENT_ROOT_DESTORY_ACK::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_MSG_5fCLIENT_5fDM_5fROOT_5fDESTROY_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_MSG_5fCLIENT_5fDM_5fROOT_5fDESTROY_2eproto {
  StaticDescriptorInitializer_MSG_5fCLIENT_5fDM_5fROOT_5fDESTROY_2eproto() {
    protobuf_AddDesc_MSG_5fCLIENT_5fDM_5fROOT_5fDESTROY_2eproto();
  }
} static_descriptor_initializer_MSG_5fCLIENT_5fDM_5fROOT_5fDESTROY_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int MSG_CLIENT_DM_ROOT_DESTORY::kTokenFieldNumber;
const int MSG_CLIENT_DM_ROOT_DESTORY::kUserNameFieldNumber;
#endif  // !_MSC_VER

MSG_CLIENT_DM_ROOT_DESTORY::MSG_CLIENT_DM_ROOT_DESTORY()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void MSG_CLIENT_DM_ROOT_DESTORY::InitAsDefaultInstance() {
}

MSG_CLIENT_DM_ROOT_DESTORY::MSG_CLIENT_DM_ROOT_DESTORY(const MSG_CLIENT_DM_ROOT_DESTORY& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void MSG_CLIENT_DM_ROOT_DESTORY::SharedCtor() {
  _cached_size_ = 0;
  token_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  username_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MSG_CLIENT_DM_ROOT_DESTORY::~MSG_CLIENT_DM_ROOT_DESTORY() {
  SharedDtor();
}

void MSG_CLIENT_DM_ROOT_DESTORY::SharedDtor() {
  if (token_ != &::google::protobuf::internal::kEmptyString) {
    delete token_;
  }
  if (username_ != &::google::protobuf::internal::kEmptyString) {
    delete username_;
  }
  if (this != default_instance_) {
  }
}

void MSG_CLIENT_DM_ROOT_DESTORY::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MSG_CLIENT_DM_ROOT_DESTORY::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MSG_CLIENT_DM_ROOT_DESTORY_descriptor_;
}

const MSG_CLIENT_DM_ROOT_DESTORY& MSG_CLIENT_DM_ROOT_DESTORY::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_MSG_5fCLIENT_5fDM_5fROOT_5fDESTROY_2eproto();  return *default_instance_;
}

MSG_CLIENT_DM_ROOT_DESTORY* MSG_CLIENT_DM_ROOT_DESTORY::default_instance_ = NULL;

MSG_CLIENT_DM_ROOT_DESTORY* MSG_CLIENT_DM_ROOT_DESTORY::New() const {
  return new MSG_CLIENT_DM_ROOT_DESTORY;
}

void MSG_CLIENT_DM_ROOT_DESTORY::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_token()) {
      if (token_ != &::google::protobuf::internal::kEmptyString) {
        token_->clear();
      }
    }
    if (has_username()) {
      if (username_ != &::google::protobuf::internal::kEmptyString) {
        username_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool MSG_CLIENT_DM_ROOT_DESTORY::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string token = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_token()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->token().data(), this->token().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_userName;
        break;
      }
      
      // optional string userName = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_userName:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_username()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->username().data(), this->username().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void MSG_CLIENT_DM_ROOT_DESTORY::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string token = 1;
  if (has_token()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->token().data(), this->token().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->token(), output);
  }
  
  // optional string userName = 2;
  if (has_username()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->username().data(), this->username().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->username(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* MSG_CLIENT_DM_ROOT_DESTORY::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional string token = 1;
  if (has_token()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->token().data(), this->token().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->token(), target);
  }
  
  // optional string userName = 2;
  if (has_username()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->username().data(), this->username().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->username(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int MSG_CLIENT_DM_ROOT_DESTORY::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string token = 1;
    if (has_token()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->token());
    }
    
    // optional string userName = 2;
    if (has_username()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->username());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MSG_CLIENT_DM_ROOT_DESTORY::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const MSG_CLIENT_DM_ROOT_DESTORY* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const MSG_CLIENT_DM_ROOT_DESTORY*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void MSG_CLIENT_DM_ROOT_DESTORY::MergeFrom(const MSG_CLIENT_DM_ROOT_DESTORY& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_token()) {
      set_token(from.token());
    }
    if (from.has_username()) {
      set_username(from.username());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void MSG_CLIENT_DM_ROOT_DESTORY::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MSG_CLIENT_DM_ROOT_DESTORY::CopyFrom(const MSG_CLIENT_DM_ROOT_DESTORY& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MSG_CLIENT_DM_ROOT_DESTORY::IsInitialized() const {
  
  return true;
}

void MSG_CLIENT_DM_ROOT_DESTORY::Swap(MSG_CLIENT_DM_ROOT_DESTORY* other) {
  if (other != this) {
    std::swap(token_, other->token_);
    std::swap(username_, other->username_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata MSG_CLIENT_DM_ROOT_DESTORY::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MSG_CLIENT_DM_ROOT_DESTORY_descriptor_;
  metadata.reflection = MSG_CLIENT_DM_ROOT_DESTORY_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int MSG_DM_CLIENT_ROOT_DESTORY_ACK::kStatusCodeFieldNumber;
#endif  // !_MSC_VER

MSG_DM_CLIENT_ROOT_DESTORY_ACK::MSG_DM_CLIENT_ROOT_DESTORY_ACK()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void MSG_DM_CLIENT_ROOT_DESTORY_ACK::InitAsDefaultInstance() {
}

MSG_DM_CLIENT_ROOT_DESTORY_ACK::MSG_DM_CLIENT_ROOT_DESTORY_ACK(const MSG_DM_CLIENT_ROOT_DESTORY_ACK& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void MSG_DM_CLIENT_ROOT_DESTORY_ACK::SharedCtor() {
  _cached_size_ = 0;
  statuscode_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MSG_DM_CLIENT_ROOT_DESTORY_ACK::~MSG_DM_CLIENT_ROOT_DESTORY_ACK() {
  SharedDtor();
}

void MSG_DM_CLIENT_ROOT_DESTORY_ACK::SharedDtor() {
  if (this != default_instance_) {
  }
}

void MSG_DM_CLIENT_ROOT_DESTORY_ACK::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MSG_DM_CLIENT_ROOT_DESTORY_ACK::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MSG_DM_CLIENT_ROOT_DESTORY_ACK_descriptor_;
}

const MSG_DM_CLIENT_ROOT_DESTORY_ACK& MSG_DM_CLIENT_ROOT_DESTORY_ACK::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_MSG_5fCLIENT_5fDM_5fROOT_5fDESTROY_2eproto();  return *default_instance_;
}

MSG_DM_CLIENT_ROOT_DESTORY_ACK* MSG_DM_CLIENT_ROOT_DESTORY_ACK::default_instance_ = NULL;

MSG_DM_CLIENT_ROOT_DESTORY_ACK* MSG_DM_CLIENT_ROOT_DESTORY_ACK::New() const {
  return new MSG_DM_CLIENT_ROOT_DESTORY_ACK;
}

void MSG_DM_CLIENT_ROOT_DESTORY_ACK::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    statuscode_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool MSG_DM_CLIENT_ROOT_DESTORY_ACK::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 statusCode = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &statuscode_)));
          set_has_statuscode();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void MSG_DM_CLIENT_ROOT_DESTORY_ACK::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional int32 statusCode = 1;
  if (has_statuscode()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->statuscode(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* MSG_DM_CLIENT_ROOT_DESTORY_ACK::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional int32 statusCode = 1;
  if (has_statuscode()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->statuscode(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int MSG_DM_CLIENT_ROOT_DESTORY_ACK::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional int32 statusCode = 1;
    if (has_statuscode()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->statuscode());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MSG_DM_CLIENT_ROOT_DESTORY_ACK::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const MSG_DM_CLIENT_ROOT_DESTORY_ACK* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const MSG_DM_CLIENT_ROOT_DESTORY_ACK*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void MSG_DM_CLIENT_ROOT_DESTORY_ACK::MergeFrom(const MSG_DM_CLIENT_ROOT_DESTORY_ACK& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_statuscode()) {
      set_statuscode(from.statuscode());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void MSG_DM_CLIENT_ROOT_DESTORY_ACK::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MSG_DM_CLIENT_ROOT_DESTORY_ACK::CopyFrom(const MSG_DM_CLIENT_ROOT_DESTORY_ACK& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MSG_DM_CLIENT_ROOT_DESTORY_ACK::IsInitialized() const {
  
  return true;
}

void MSG_DM_CLIENT_ROOT_DESTORY_ACK::Swap(MSG_DM_CLIENT_ROOT_DESTORY_ACK* other) {
  if (other != this) {
    std::swap(statuscode_, other->statuscode_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata MSG_DM_CLIENT_ROOT_DESTORY_ACK::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MSG_DM_CLIENT_ROOT_DESTORY_ACK_descriptor_;
  metadata.reflection = MSG_DM_CLIENT_ROOT_DESTORY_ACK_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

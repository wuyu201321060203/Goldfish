// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "MSG_DC_DM_CONFIG_DELETE.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* MSG_DC_DM_CONFIG_DELETE_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MSG_DC_DM_CONFIG_DELETE_reflection_ = NULL;
const ::google::protobuf::Descriptor* MSG_DM_DC_CONFIG_DELETE_ACK_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MSG_DM_DC_CONFIG_DELETE_ACK_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_MSG_5fDC_5fDM_5fCONFIG_5fDELETE_2eproto() {
  protobuf_AddDesc_MSG_5fDC_5fDM_5fCONFIG_5fDELETE_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "MSG_DC_DM_CONFIG_DELETE.proto");
  GOOGLE_CHECK(file != NULL);
  MSG_DC_DM_CONFIG_DELETE_descriptor_ = file->message_type(0);
  static const int MSG_DC_DM_CONFIG_DELETE_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSG_DC_DM_CONFIG_DELETE, domainname_),
  };
  MSG_DC_DM_CONFIG_DELETE_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      MSG_DC_DM_CONFIG_DELETE_descriptor_,
      MSG_DC_DM_CONFIG_DELETE::default_instance_,
      MSG_DC_DM_CONFIG_DELETE_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSG_DC_DM_CONFIG_DELETE, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSG_DC_DM_CONFIG_DELETE, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(MSG_DC_DM_CONFIG_DELETE));
  MSG_DM_DC_CONFIG_DELETE_ACK_descriptor_ = file->message_type(1);
  static const int MSG_DM_DC_CONFIG_DELETE_ACK_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSG_DM_DC_CONFIG_DELETE_ACK, statuscode_),
  };
  MSG_DM_DC_CONFIG_DELETE_ACK_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      MSG_DM_DC_CONFIG_DELETE_ACK_descriptor_,
      MSG_DM_DC_CONFIG_DELETE_ACK::default_instance_,
      MSG_DM_DC_CONFIG_DELETE_ACK_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSG_DM_DC_CONFIG_DELETE_ACK, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSG_DM_DC_CONFIG_DELETE_ACK, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(MSG_DM_DC_CONFIG_DELETE_ACK));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_MSG_5fDC_5fDM_5fCONFIG_5fDELETE_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    MSG_DC_DM_CONFIG_DELETE_descriptor_, &MSG_DC_DM_CONFIG_DELETE::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    MSG_DM_DC_CONFIG_DELETE_ACK_descriptor_, &MSG_DM_DC_CONFIG_DELETE_ACK::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_MSG_5fDC_5fDM_5fCONFIG_5fDELETE_2eproto() {
  delete MSG_DC_DM_CONFIG_DELETE::default_instance_;
  delete MSG_DC_DM_CONFIG_DELETE_reflection_;
  delete MSG_DM_DC_CONFIG_DELETE_ACK::default_instance_;
  delete MSG_DM_DC_CONFIG_DELETE_ACK_reflection_;
}

void protobuf_AddDesc_MSG_5fDC_5fDM_5fCONFIG_5fDELETE_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\035MSG_DC_DM_CONFIG_DELETE.proto\"-\n\027MSG_D"
    "C_DM_CONFIG_DELETE\022\022\n\ndomainName\030\001 \001(\t\"1"
    "\n\033MSG_DM_DC_CONFIG_DELETE_ACK\022\022\n\nstatusC"
    "ode\030\001 \001(\005", 129);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "MSG_DC_DM_CONFIG_DELETE.proto", &protobuf_RegisterTypes);
  MSG_DC_DM_CONFIG_DELETE::default_instance_ = new MSG_DC_DM_CONFIG_DELETE();
  MSG_DM_DC_CONFIG_DELETE_ACK::default_instance_ = new MSG_DM_DC_CONFIG_DELETE_ACK();
  MSG_DC_DM_CONFIG_DELETE::default_instance_->InitAsDefaultInstance();
  MSG_DM_DC_CONFIG_DELETE_ACK::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_MSG_5fDC_5fDM_5fCONFIG_5fDELETE_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_MSG_5fDC_5fDM_5fCONFIG_5fDELETE_2eproto {
  StaticDescriptorInitializer_MSG_5fDC_5fDM_5fCONFIG_5fDELETE_2eproto() {
    protobuf_AddDesc_MSG_5fDC_5fDM_5fCONFIG_5fDELETE_2eproto();
  }
} static_descriptor_initializer_MSG_5fDC_5fDM_5fCONFIG_5fDELETE_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int MSG_DC_DM_CONFIG_DELETE::kDomainNameFieldNumber;
#endif  // !_MSC_VER

MSG_DC_DM_CONFIG_DELETE::MSG_DC_DM_CONFIG_DELETE()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void MSG_DC_DM_CONFIG_DELETE::InitAsDefaultInstance() {
}

MSG_DC_DM_CONFIG_DELETE::MSG_DC_DM_CONFIG_DELETE(const MSG_DC_DM_CONFIG_DELETE& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void MSG_DC_DM_CONFIG_DELETE::SharedCtor() {
  _cached_size_ = 0;
  domainname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MSG_DC_DM_CONFIG_DELETE::~MSG_DC_DM_CONFIG_DELETE() {
  SharedDtor();
}

void MSG_DC_DM_CONFIG_DELETE::SharedDtor() {
  if (domainname_ != &::google::protobuf::internal::kEmptyString) {
    delete domainname_;
  }
  if (this != default_instance_) {
  }
}

void MSG_DC_DM_CONFIG_DELETE::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MSG_DC_DM_CONFIG_DELETE::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MSG_DC_DM_CONFIG_DELETE_descriptor_;
}

const MSG_DC_DM_CONFIG_DELETE& MSG_DC_DM_CONFIG_DELETE::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_MSG_5fDC_5fDM_5fCONFIG_5fDELETE_2eproto();  return *default_instance_;
}

MSG_DC_DM_CONFIG_DELETE* MSG_DC_DM_CONFIG_DELETE::default_instance_ = NULL;

MSG_DC_DM_CONFIG_DELETE* MSG_DC_DM_CONFIG_DELETE::New() const {
  return new MSG_DC_DM_CONFIG_DELETE;
}

void MSG_DC_DM_CONFIG_DELETE::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_domainname()) {
      if (domainname_ != &::google::protobuf::internal::kEmptyString) {
        domainname_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool MSG_DC_DM_CONFIG_DELETE::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string domainName = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_domainname()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->domainname().data(), this->domainname().length(),
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

void MSG_DC_DM_CONFIG_DELETE::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional string domainName = 1;
  if (has_domainname()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->domainname().data(), this->domainname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->domainname(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* MSG_DC_DM_CONFIG_DELETE::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional string domainName = 1;
  if (has_domainname()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->domainname().data(), this->domainname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->domainname(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int MSG_DC_DM_CONFIG_DELETE::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string domainName = 1;
    if (has_domainname()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->domainname());
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

void MSG_DC_DM_CONFIG_DELETE::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const MSG_DC_DM_CONFIG_DELETE* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const MSG_DC_DM_CONFIG_DELETE*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void MSG_DC_DM_CONFIG_DELETE::MergeFrom(const MSG_DC_DM_CONFIG_DELETE& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_domainname()) {
      set_domainname(from.domainname());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void MSG_DC_DM_CONFIG_DELETE::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MSG_DC_DM_CONFIG_DELETE::CopyFrom(const MSG_DC_DM_CONFIG_DELETE& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MSG_DC_DM_CONFIG_DELETE::IsInitialized() const {
  
  return true;
}

void MSG_DC_DM_CONFIG_DELETE::Swap(MSG_DC_DM_CONFIG_DELETE* other) {
  if (other != this) {
    std::swap(domainname_, other->domainname_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata MSG_DC_DM_CONFIG_DELETE::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MSG_DC_DM_CONFIG_DELETE_descriptor_;
  metadata.reflection = MSG_DC_DM_CONFIG_DELETE_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int MSG_DM_DC_CONFIG_DELETE_ACK::kStatusCodeFieldNumber;
#endif  // !_MSC_VER

MSG_DM_DC_CONFIG_DELETE_ACK::MSG_DM_DC_CONFIG_DELETE_ACK()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void MSG_DM_DC_CONFIG_DELETE_ACK::InitAsDefaultInstance() {
}

MSG_DM_DC_CONFIG_DELETE_ACK::MSG_DM_DC_CONFIG_DELETE_ACK(const MSG_DM_DC_CONFIG_DELETE_ACK& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void MSG_DM_DC_CONFIG_DELETE_ACK::SharedCtor() {
  _cached_size_ = 0;
  statuscode_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MSG_DM_DC_CONFIG_DELETE_ACK::~MSG_DM_DC_CONFIG_DELETE_ACK() {
  SharedDtor();
}

void MSG_DM_DC_CONFIG_DELETE_ACK::SharedDtor() {
  if (this != default_instance_) {
  }
}

void MSG_DM_DC_CONFIG_DELETE_ACK::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MSG_DM_DC_CONFIG_DELETE_ACK::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MSG_DM_DC_CONFIG_DELETE_ACK_descriptor_;
}

const MSG_DM_DC_CONFIG_DELETE_ACK& MSG_DM_DC_CONFIG_DELETE_ACK::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_MSG_5fDC_5fDM_5fCONFIG_5fDELETE_2eproto();  return *default_instance_;
}

MSG_DM_DC_CONFIG_DELETE_ACK* MSG_DM_DC_CONFIG_DELETE_ACK::default_instance_ = NULL;

MSG_DM_DC_CONFIG_DELETE_ACK* MSG_DM_DC_CONFIG_DELETE_ACK::New() const {
  return new MSG_DM_DC_CONFIG_DELETE_ACK;
}

void MSG_DM_DC_CONFIG_DELETE_ACK::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    statuscode_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool MSG_DM_DC_CONFIG_DELETE_ACK::MergePartialFromCodedStream(
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

void MSG_DM_DC_CONFIG_DELETE_ACK::SerializeWithCachedSizes(
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

::google::protobuf::uint8* MSG_DM_DC_CONFIG_DELETE_ACK::SerializeWithCachedSizesToArray(
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

int MSG_DM_DC_CONFIG_DELETE_ACK::ByteSize() const {
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

void MSG_DM_DC_CONFIG_DELETE_ACK::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const MSG_DM_DC_CONFIG_DELETE_ACK* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const MSG_DM_DC_CONFIG_DELETE_ACK*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void MSG_DM_DC_CONFIG_DELETE_ACK::MergeFrom(const MSG_DM_DC_CONFIG_DELETE_ACK& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_statuscode()) {
      set_statuscode(from.statuscode());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void MSG_DM_DC_CONFIG_DELETE_ACK::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MSG_DM_DC_CONFIG_DELETE_ACK::CopyFrom(const MSG_DM_DC_CONFIG_DELETE_ACK& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MSG_DM_DC_CONFIG_DELETE_ACK::IsInitialized() const {
  
  return true;
}

void MSG_DM_DC_CONFIG_DELETE_ACK::Swap(MSG_DM_DC_CONFIG_DELETE_ACK* other) {
  if (other != this) {
    std::swap(statuscode_, other->statuscode_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata MSG_DM_DC_CONFIG_DELETE_ACK::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MSG_DM_DC_CONFIG_DELETE_ACK_descriptor_;
  metadata.reflection = MSG_DM_DC_CONFIG_DELETE_ACK_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

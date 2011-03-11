// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client.proto

#ifndef PROTOBUF_client_2eproto__INCLUDED
#define PROTOBUF_client_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace Client {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_client_2eproto();
void protobuf_AssignDesc_client_2eproto();
void protobuf_ShutdownFile_client_2eproto();

class RobotMessage;
class RobotMessage_NeighborRobots;
class RobotMessage_NeighborPucks;
class Client;

// ===================================================================

class RobotMessage_NeighborRobots : public ::google::protobuf::Message {
 public:
  RobotMessage_NeighborRobots();
  virtual ~RobotMessage_NeighborRobots();
  
  RobotMessage_NeighborRobots(const RobotMessage_NeighborRobots& from);
  
  inline RobotMessage_NeighborRobots& operator=(const RobotMessage_NeighborRobots& from) {
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
  static const RobotMessage_NeighborRobots& default_instance();
  
  void Swap(RobotMessage_NeighborRobots* other);
  
  // implements Message ----------------------------------------------
  
  RobotMessage_NeighborRobots* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RobotMessage_NeighborRobots& from);
  void MergeFrom(const RobotMessage_NeighborRobots& from);
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
  
  // required int32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);
  
  // required float position = 2;
  inline bool has_position() const;
  inline void clear_position();
  static const int kPositionFieldNumber = 2;
  inline float position() const;
  inline void set_position(float value);
  
  // optional float speed = 3;
  inline bool has_speed() const;
  inline void clear_speed();
  static const int kSpeedFieldNumber = 3;
  inline float speed() const;
  inline void set_speed(float value);
  
  // @@protoc_insertion_point(class_scope:Client.RobotMessage.NeighborRobots)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_position();
  inline void clear_has_position();
  inline void set_has_speed();
  inline void clear_has_speed();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 id_;
  float position_;
  float speed_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_client_2eproto();
  friend void protobuf_AssignDesc_client_2eproto();
  friend void protobuf_ShutdownFile_client_2eproto();
  
  void InitAsDefaultInstance();
  static RobotMessage_NeighborRobots* default_instance_;
};
// -------------------------------------------------------------------

class RobotMessage_NeighborPucks : public ::google::protobuf::Message {
 public:
  RobotMessage_NeighborPucks();
  virtual ~RobotMessage_NeighborPucks();
  
  RobotMessage_NeighborPucks(const RobotMessage_NeighborPucks& from);
  
  inline RobotMessage_NeighborPucks& operator=(const RobotMessage_NeighborPucks& from) {
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
  static const RobotMessage_NeighborPucks& default_instance();
  
  void Swap(RobotMessage_NeighborPucks* other);
  
  // implements Message ----------------------------------------------
  
  RobotMessage_NeighborPucks* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RobotMessage_NeighborPucks& from);
  void MergeFrom(const RobotMessage_NeighborPucks& from);
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
  
  // required float position = 1;
  inline bool has_position() const;
  inline void clear_position();
  static const int kPositionFieldNumber = 1;
  inline float position() const;
  inline void set_position(float value);
  
  // optional bool isHeld = 2;
  inline bool has_isheld() const;
  inline void clear_isheld();
  static const int kIsHeldFieldNumber = 2;
  inline bool isheld() const;
  inline void set_isheld(bool value);
  
  // @@protoc_insertion_point(class_scope:Client.RobotMessage.NeighborPucks)
 private:
  inline void set_has_position();
  inline void clear_has_position();
  inline void set_has_isheld();
  inline void clear_has_isheld();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  float position_;
  bool isheld_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_client_2eproto();
  friend void protobuf_AssignDesc_client_2eproto();
  friend void protobuf_ShutdownFile_client_2eproto();
  
  void InitAsDefaultInstance();
  static RobotMessage_NeighborPucks* default_instance_;
};
// -------------------------------------------------------------------

class RobotMessage : public ::google::protobuf::Message {
 public:
  RobotMessage();
  virtual ~RobotMessage();
  
  RobotMessage(const RobotMessage& from);
  
  inline RobotMessage& operator=(const RobotMessage& from) {
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
  static const RobotMessage& default_instance();
  
  void Swap(RobotMessage* other);
  
  // implements Message ----------------------------------------------
  
  RobotMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RobotMessage& from);
  void MergeFrom(const RobotMessage& from);
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
  
  typedef RobotMessage_NeighborRobots NeighborRobots;
  typedef RobotMessage_NeighborPucks NeighborPucks;
  
  // accessors -------------------------------------------------------
  
  // repeated .Client.RobotMessage.NeighborRobots neighbors = 1;
  inline int neighbors_size() const;
  inline void clear_neighbors();
  static const int kNeighborsFieldNumber = 1;
  inline const ::Client::RobotMessage_NeighborRobots& neighbors(int index) const;
  inline ::Client::RobotMessage_NeighborRobots* mutable_neighbors(int index);
  inline ::Client::RobotMessage_NeighborRobots* add_neighbors();
  inline const ::google::protobuf::RepeatedPtrField< ::Client::RobotMessage_NeighborRobots >&
      neighbors() const;
  inline ::google::protobuf::RepeatedPtrField< ::Client::RobotMessage_NeighborRobots >*
      mutable_neighbors();
  
  // repeated .Client.RobotMessage.NeighborPucks pucks = 2;
  inline int pucks_size() const;
  inline void clear_pucks();
  static const int kPucksFieldNumber = 2;
  inline const ::Client::RobotMessage_NeighborPucks& pucks(int index) const;
  inline ::Client::RobotMessage_NeighborPucks* mutable_pucks(int index);
  inline ::Client::RobotMessage_NeighborPucks* add_pucks();
  inline const ::google::protobuf::RepeatedPtrField< ::Client::RobotMessage_NeighborPucks >&
      pucks() const;
  inline ::google::protobuf::RepeatedPtrField< ::Client::RobotMessage_NeighborPucks >*
      mutable_pucks();
  
  // @@protoc_insertion_point(class_scope:Client.RobotMessage)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::Client::RobotMessage_NeighborRobots > neighbors_;
  ::google::protobuf::RepeatedPtrField< ::Client::RobotMessage_NeighborPucks > pucks_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_client_2eproto();
  friend void protobuf_AssignDesc_client_2eproto();
  friend void protobuf_ShutdownFile_client_2eproto();
  
  void InitAsDefaultInstance();
  static RobotMessage* default_instance_;
};
// -------------------------------------------------------------------

class Client : public ::google::protobuf::Message {
 public:
  Client();
  virtual ~Client();
  
  Client(const Client& from);
  
  inline Client& operator=(const Client& from) {
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
  static const Client& default_instance();
  
  void Swap(Client* other);
  
  // implements Message ----------------------------------------------
  
  Client* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Client& from);
  void MergeFrom(const Client& from);
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
  
  // repeated .Client.RobotMessage message = 1;
  inline int message_size() const;
  inline void clear_message();
  static const int kMessageFieldNumber = 1;
  inline const ::Client::RobotMessage& message(int index) const;
  inline ::Client::RobotMessage* mutable_message(int index);
  inline ::Client::RobotMessage* add_message();
  inline const ::google::protobuf::RepeatedPtrField< ::Client::RobotMessage >&
      message() const;
  inline ::google::protobuf::RepeatedPtrField< ::Client::RobotMessage >*
      mutable_message();
  
  // @@protoc_insertion_point(class_scope:Client.Client)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::Client::RobotMessage > message_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_client_2eproto();
  friend void protobuf_AssignDesc_client_2eproto();
  friend void protobuf_ShutdownFile_client_2eproto();
  
  void InitAsDefaultInstance();
  static Client* default_instance_;
};
// ===================================================================


// ===================================================================

// RobotMessage_NeighborRobots

// required int32 id = 1;
inline bool RobotMessage_NeighborRobots::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RobotMessage_NeighborRobots::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RobotMessage_NeighborRobots::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RobotMessage_NeighborRobots::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 RobotMessage_NeighborRobots::id() const {
  return id_;
}
inline void RobotMessage_NeighborRobots::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
}

// required float position = 2;
inline bool RobotMessage_NeighborRobots::has_position() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RobotMessage_NeighborRobots::set_has_position() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RobotMessage_NeighborRobots::clear_has_position() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RobotMessage_NeighborRobots::clear_position() {
  position_ = 0;
  clear_has_position();
}
inline float RobotMessage_NeighborRobots::position() const {
  return position_;
}
inline void RobotMessage_NeighborRobots::set_position(float value) {
  set_has_position();
  position_ = value;
}

// optional float speed = 3;
inline bool RobotMessage_NeighborRobots::has_speed() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void RobotMessage_NeighborRobots::set_has_speed() {
  _has_bits_[0] |= 0x00000004u;
}
inline void RobotMessage_NeighborRobots::clear_has_speed() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void RobotMessage_NeighborRobots::clear_speed() {
  speed_ = 0;
  clear_has_speed();
}
inline float RobotMessage_NeighborRobots::speed() const {
  return speed_;
}
inline void RobotMessage_NeighborRobots::set_speed(float value) {
  set_has_speed();
  speed_ = value;
}

// -------------------------------------------------------------------

// RobotMessage_NeighborPucks

// required float position = 1;
inline bool RobotMessage_NeighborPucks::has_position() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RobotMessage_NeighborPucks::set_has_position() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RobotMessage_NeighborPucks::clear_has_position() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RobotMessage_NeighborPucks::clear_position() {
  position_ = 0;
  clear_has_position();
}
inline float RobotMessage_NeighborPucks::position() const {
  return position_;
}
inline void RobotMessage_NeighborPucks::set_position(float value) {
  set_has_position();
  position_ = value;
}

// optional bool isHeld = 2;
inline bool RobotMessage_NeighborPucks::has_isheld() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RobotMessage_NeighborPucks::set_has_isheld() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RobotMessage_NeighborPucks::clear_has_isheld() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RobotMessage_NeighborPucks::clear_isheld() {
  isheld_ = false;
  clear_has_isheld();
}
inline bool RobotMessage_NeighborPucks::isheld() const {
  return isheld_;
}
inline void RobotMessage_NeighborPucks::set_isheld(bool value) {
  set_has_isheld();
  isheld_ = value;
}

// -------------------------------------------------------------------

// RobotMessage

// repeated .Client.RobotMessage.NeighborRobots neighbors = 1;
inline int RobotMessage::neighbors_size() const {
  return neighbors_.size();
}
inline void RobotMessage::clear_neighbors() {
  neighbors_.Clear();
}
inline const ::Client::RobotMessage_NeighborRobots& RobotMessage::neighbors(int index) const {
  return neighbors_.Get(index);
}
inline ::Client::RobotMessage_NeighborRobots* RobotMessage::mutable_neighbors(int index) {
  return neighbors_.Mutable(index);
}
inline ::Client::RobotMessage_NeighborRobots* RobotMessage::add_neighbors() {
  return neighbors_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Client::RobotMessage_NeighborRobots >&
RobotMessage::neighbors() const {
  return neighbors_;
}
inline ::google::protobuf::RepeatedPtrField< ::Client::RobotMessage_NeighborRobots >*
RobotMessage::mutable_neighbors() {
  return &neighbors_;
}

// repeated .Client.RobotMessage.NeighborPucks pucks = 2;
inline int RobotMessage::pucks_size() const {
  return pucks_.size();
}
inline void RobotMessage::clear_pucks() {
  pucks_.Clear();
}
inline const ::Client::RobotMessage_NeighborPucks& RobotMessage::pucks(int index) const {
  return pucks_.Get(index);
}
inline ::Client::RobotMessage_NeighborPucks* RobotMessage::mutable_pucks(int index) {
  return pucks_.Mutable(index);
}
inline ::Client::RobotMessage_NeighborPucks* RobotMessage::add_pucks() {
  return pucks_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Client::RobotMessage_NeighborPucks >&
RobotMessage::pucks() const {
  return pucks_;
}
inline ::google::protobuf::RepeatedPtrField< ::Client::RobotMessage_NeighborPucks >*
RobotMessage::mutable_pucks() {
  return &pucks_;
}

// -------------------------------------------------------------------

// Client

// repeated .Client.RobotMessage message = 1;
inline int Client::message_size() const {
  return message_.size();
}
inline void Client::clear_message() {
  message_.Clear();
}
inline const ::Client::RobotMessage& Client::message(int index) const {
  return message_.Get(index);
}
inline ::Client::RobotMessage* Client::mutable_message(int index) {
  return message_.Mutable(index);
}
inline ::Client::RobotMessage* Client::add_message() {
  return message_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Client::RobotMessage >&
Client::message() const {
  return message_;
}
inline ::google::protobuf::RepeatedPtrField< ::Client::RobotMessage >*
Client::mutable_message() {
  return &message_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Client

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_client_2eproto__INCLUDED
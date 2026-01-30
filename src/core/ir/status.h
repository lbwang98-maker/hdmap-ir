#pragma once
#include <optional>
#include <string>

namespace hdmap::ir {

enum class StatusCode { kOk = 0, kInvalidArgument, kNotFound, kInternal };

class Status {
 public:
  Status() : code_(StatusCode::kOk) {}
  Status(StatusCode code, std::string msg = "") : code_(code), msg_(std::move(msg)) {}

  bool ok() const {
    return code_ == StatusCode::kOk;
  }
  StatusCode code() const {
    return code_;
  }
  const std::string msg() const {
    return msg_;
  }

 private:
  StatusCode code_;
  std::string msg_;
};

inline Status OkStatus() {
  return Status();
}

template <typename T>
class StatusOr {
 public:
  StatusOr(const T& value) : status_(OkStatus()), value_(value) {}
  StatusOr(T&& value) : status_(OkStatus()), value_(std::move(value)) {}
  StatusOr(const Status& status) : status_(status), value_(std::nullopt) {}

  bool ok() const {
    return status_.ok();
  }

  const Status& status() const {
    return status_;
  }
  const T& value() const {
    return *value_;
  }
  T& value() {
    return *value_;
  }

 private:
  Status status_;
  std::optional<T> value_;
};

}  // namespace hdmap::ir
//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   exceptions.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30

#pragma once

#include <stdexcept>

namespace fv::exceptions {

namespace detail {

class base : public std::runtime_error {
 public:
  explicit base(const char* what) : std::runtime_error(what) {}
};
}  // namespace detail

/// Typedef for base exception to get better name in catch expression.
typedef detail::base all;

// - customized exceptions -


class invalid_state : public detail::base {
 public:
  explicit invalid_state(const char* message = "invalid object state")
      : detail::base(message) {}
};


class invalid_parameter : public detail::base {
 public:
  explicit invalid_parameter(const char* message = "invalid parameter")
      : detail::base(message) {}
};


class cannot_create : public detail::base {
 public:
  explicit cannot_create(const char* message = "cannot create")
      : detail::base(message) {}
};


class connection_error : public detail::base {
 public:
  explicit connection_error(const char* message = "connection error")
      : detail::base(message) {}
};


class core_error : public detail::base {
 public:
  explicit core_error(const char* message = "core error")
      : detail::base(message) {}
};


class timeout : public detail::base {
 public:
  explicit timeout(const char* message = "timeout") : detail::base(message) {}
};


class disconnected : public detail::base {
 public:
  explicit disconnected(const char* message = "disconnected")
      : detail::base(message) {}
};

class unknown_command : public detail::base {
 public:
  explicit unknown_command(const char* message = "unknown_command")
      : detail::base(message) {}
};


class protocol_error : public detail::base {
 public:
  explicit protocol_error(const char* message = "protocol_error")
      : detail::base(message) {}
};


class cannceled : public detail::base {
 public:
  explicit cannceled(const char* message = "cannceled")
      : detail::base(message) {}
};

}  // namespace fv::exceptions

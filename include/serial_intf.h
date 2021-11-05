//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   serial_intf.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-31

#pragma once

#include "exceptions.h"
#include <memory>
#include <string>
#include <string_view>
#include <array>

namespace fv::serial {

enum class StopBits : int { stop_1 = 1, stop_1_5 = 2, stop_2 = 3 };

enum class Parity : int { none = 0, odd = 1, even = 2 };

enum class FlowControl : int { none = 0, xonff = 1, hw = 2 };

enum class BDSpeed : int {
  bd0 = 0,
  bd50 = 50,
  bd75 = 75,
  bd110 = 110,
  bd134 = 134,
  bd150 = 150,
  bd200 = 200,
  bd300 = 300,
  bd600 = 600,
  bd1200 = 1200,
  bd1800 = 1800,
  bd2400 = 2400,
  bd4800 = 4800,
  bd9600 = 9600,
  bd19200 = 19200,
  bd38400 = 38400,
  bd57600 = 57600,
  bd115200 = 115200,
  bd12800 = 128000
};

static constexpr auto all_speeds = std::array{
    // BDSpeed::bd0,
    BDSpeed::bd50,     BDSpeed::bd75,    BDSpeed::bd110,   BDSpeed::bd134,
    BDSpeed::bd150,    BDSpeed::bd200,   BDSpeed::bd300,   BDSpeed::bd600,
    BDSpeed::bd1200,   BDSpeed::bd1800,  BDSpeed::bd2400,  BDSpeed::bd4800,
    BDSpeed::bd9600,   BDSpeed::bd19200, BDSpeed::bd38400, BDSpeed::bd57600,
    BDSpeed::bd115200, BDSpeed::bd12800};

enum class DataBits : int { b5 = 5, b6 = 6, b7 = 7, b8 = 8 };

static constexpr auto all_bits =
    std::array{DataBits::b5, DataBits::b6, DataBits::b7, DataBits::b8};

struct ISerial {
public:
  virtual ~ISerial() = default;

  virtual void open() = 0;
  virtual void close() = 0;
  virtual bool isOpen() const = 0;
  virtual uint64_t numberOfWaitingBytes() = 0;
  virtual std::string read(size_t maxchars = 0, size_t timeout = 0) = 0;
  virtual void write(const std::string_view &data) = 0;
  // virtual void flush() = 0;

  virtual ISerial &withTimeout(uint64_t tm) = 0;
  virtual uint64_t getTimeout() const = 0;

  virtual void clear() = 0;
  virtual ISerial &withDeviceLocation(const std::string_view &port) = 0;
  virtual std::string getLocation() const = 0;

  virtual ISerial &withHWinfo(uint16_t vid, uint16_t pid) = 0;
  virtual uint16_t getPID() const = 0;
  virtual uint16_t getVID() const = 0;

  virtual ISerial &withVendorName(const std::string_view &name) = 0;
  virtual std::string getVendorName() const = 0;

  virtual ISerial &withDeviceName(const std::string_view &name) = 0;
  virtual std::string getDeviceName() const = 0;

  virtual ISerial &withBdSpeed(BDSpeed speed) = 0;
  virtual BDSpeed getBdSpeed() const = 0;

  virtual ISerial &withParity(Parity par) = 0;
  virtual Parity getParity() const = 0;

  virtual ISerial &withStopBits(StopBits bits) = 0;
  virtual StopBits getStiopBits() const = 0;

  virtual ISerial &withFlowControl(FlowControl flw) = 0;
  virtual FlowControl getFlowControl() const = 0;

  virtual ISerial &withDataBits(DataBits flw) = 0;
  virtual DataBits getDataBits() const = 0;

  struct Factory {
    static std::unique_ptr<ISerial> createUnique();
  };
};

} // namespace fv::serial

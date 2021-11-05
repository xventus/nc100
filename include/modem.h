//
//  xmodem.h
//  base
//
//  Created by Petr Vanek on 18.09.2021.
//

#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include "serial_intf.h"

namespace fv {

class Modem {

public:
  enum class State {
    init = 1,
    timeouted,
    blockNum,
    blockNumErr,
    invBlockNum,
    data,
    crc,
    crcErr,
    end,
    cancelled
  };

  using tcallback = std::function<bool(State, uint32_t, const std::string_view&)>;

private:
  static constexpr char SOH = 0x01;
  static constexpr char STX = 0x02;
  static constexpr char EOT = 0x04;
  static constexpr char ACK = 0x06;
  static constexpr char NAK = 0x15;
  static constexpr char CAN = 0x18;
  static constexpr char ETB = 0x17;
  static constexpr char CTRLZ = 0x1A;
  static constexpr size_t ONE_SEC = 1000;
  static constexpr size_t blkSize = 128;
  uint32_t _maxretry{25};
  std::unique_ptr<serial::ISerial> _serial;
  uint8_t _defPadding{CTRLZ};
  bool _stripPadding{true};
  bool _ignoreBlockNmber{false};
  std::vector<tcallback> _callback;

public:
  Modem(std::unique_ptr<serial::ISerial> s) : _serial(std::move(s)) {}

  void open();
  void close();
  bool isOpened() const;

  // xmodem 128 octets data block
  std::string X128Receive();

  // xmodem 128 octets data block
  void X128Send(const std::string_view &data);

  Modem &addCallback(const tcallback &cb) {
    _callback.emplace_back(cb);
    return *this;
  }

  void removeCallbacks() { _callback.clear(); }

  Modem &withPaddingByte(uint8_t pad) {
    _defPadding = pad;
    return *this;
  }

  uint8_t getPaddingByte() const { return _defPadding; }

  Modem &withStripPadding(bool doStrip) {
    _stripPadding = doStrip;
    return *this;
  }

  bool isStripPadding() const { return _stripPadding; }

  Modem &withIgnoreBlockNumber(bool ignore) {
    _ignoreBlockNmber = ignore;
    return *this;
  }

  bool isIgnoreBlockNumber() const { return _ignoreBlockNmber; }

private:
  void aetReceiver(void);

  bool callback(State s, uint32_t p, const std::string_view& data);
};

} // namespace fv

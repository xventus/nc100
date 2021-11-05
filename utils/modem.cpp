//
//  xmodem.cpp
//  base
//
//  Created by Petr Vanek on 18.09.2021.
//

#include "../include/modem.h"
#include "../include/crc.h"
#include <iostream>

#include "../include/hex_stream_formatter.h"

namespace fv {

template <typename Bench, typename Callback>
void call_watch_timeout(Bench f, Callback c) {
  try {
    f();
  } catch (const exceptions::timeout &ex) {
    c();
  }
}

bool Modem::callback(State s, uint32_t p, const std::string_view& data) {
  auto rc = true;
  for (const auto &c : _callback) {
    auto r = c(s, p, data);
    if (r == false && rc) {
      rc = false;
    }
  }
  return rc;
}

void Modem::open() { _serial->open(); }

void Modem::close() { _serial->close(); }

bool Modem::isOpened() const { return _serial->isOpen(); }

void Modem::aetReceiver() {
  call_watch_timeout([&]() { _serial->read(); },
                     [&]() {

                     });
}

void Modem::X128Send(const std::string_view &data) {

  State state = State::init;
  std::string rc;
  std::string block;
  std::string sendBuffer;
  std::string recvBuffer;
  uint8_t blockNo = 1;
  bool init = false;
  auto run = true;

  while (true) {

    if (!run) {
      break;
    }

    switch (state) {
    case State::crc: {
      call_watch_timeout([&]() { recvBuffer = _serial->read(1, 2 * ONE_SEC); },
                         [&]() {
                           run = callback(State::timeouted, blockNo, sendBuffer);
                           recvBuffer.clear();
                         });

      if (!recvBuffer.empty()) {

        switch (recvBuffer[0]) {
        case ACK: // Start of Header, 128 bytes
          sendBuffer = ETB;
          _serial->write(sendBuffer);
          state = State::end;
          break;
        default:
          break;
        }
      }
      break;
    }

    case State::blockNum: {
      uint8_t sum = 0;
      auto start = (blockNo - 1) * blkSize;
      auto blockLen = ((start + blkSize) > data.size())
                          ? (blkSize - (start + blkSize - data.size()))
                          : blkSize;
      blockLen = (start >= data.size()) ? 0 : blockLen;

      if (blockLen > 0) {
        sendBuffer.clear();
        sendBuffer += SOH;
        sendBuffer += blockNo;
        sendBuffer += static_cast<uint8_t>(255 - blockNo);
        sendBuffer += data.substr(start, blockLen);

        if ((blkSize - blockLen) != 0) {
          std::string padding;
          padding.assign(blkSize - blockLen, _defPadding);
          sendBuffer.append(padding);
        }

        std::for_each(sendBuffer.begin() + 3, sendBuffer.begin() + 3 + blkSize,
                      [&](uint8_t n) { sum += n; });

        sendBuffer += sum;
        _serial->write(sendBuffer);

        state = State::init;
        continue;

      } else {
        // end of data -> EOT
        sendBuffer = EOT;
        _serial->write(sendBuffer);
        state = State::crc;
        continue;
      }
    } break;

    case State::init: {

      call_watch_timeout([&]() { recvBuffer = _serial->read(1, 2 * ONE_SEC); },
                         [&]() { run = callback(State::timeouted, blockNo, sendBuffer); });

      if (!recvBuffer.empty()) {

        switch (recvBuffer[0]) {
        case ACK: // Start of Header, 128 bytes
          state = State::blockNum;
          run = callback(State::blockNum, blockNo, sendBuffer);
          blockNo++;
          continue;
          break;

        case NAK:
          state = State::blockNum;
          if (!init) {
            run = callback(State::init, blockNo, sendBuffer);
            init = true;
          } else {

            run = callback(State::blockNumErr, blockNo, sendBuffer);
          }
          continue;

        default:
          break;
        }
      } else {
        run = callback(State::timeouted, blockNo, sendBuffer);
      }
    } break;
    default:
      break;
    }

    if (state == State::end) {
      run = callback(State::end, blockNo, sendBuffer);
      aetReceiver();
      break;
    }
  }
}

std::string Modem::X128Receive() {
  State state = State::init;
  std::string rc;
  std::string block;
  size_t blkPos = 0;
  std::string sendBuffer;
  std::string recvBuffer;
  uint8_t blockNo = 0;
  uint8_t lastBlockNo = 0;
  uint8_t sum = 0;
  auto run = true;

  sendBuffer = NAK; // initial
  while (true) {

    if (!run) {
      throw exceptions::cannceled();
      break;
    }

    if (!sendBuffer.empty()) {
      _serial->write(sendBuffer);
    }

    if (state == State::end) {
      run = callback(State::end, blockNo, "");
      break;
    }

    if (state == State::init) {
      sendBuffer.clear();
      blkPos = 0;
      block.clear();
      sum = 0;
    }

    call_watch_timeout([&]() { recvBuffer = _serial->read(1, 2 * ONE_SEC); },
                       [&]() {
                         run = callback(State::timeouted, blockNo, recvBuffer);
                         recvBuffer.clear();
                       });

    if (!recvBuffer.empty()) {

      switch (state) {

      case State::blockNum:
        blockNo = recvBuffer[0];
        if (lastBlockNo == 0) {
          lastBlockNo = blockNo - 1; // overflow if  blockNo == 0 --> invalid
        } // initial numbering, some devices started != 1
        state = State::invBlockNum;
        run = callback(State::blockNum, blockNo, "");
        continue;
        break;

      case State::invBlockNum: {
        state = State::data;

        if (static_cast<uint8_t>(255 - blockNo) !=
            static_cast<uint8_t>(recvBuffer[0])) {
          throw exceptions::protocol_error("inv block number error");
          break;
        }
        continue;
      } break;

      case State::data:
        // append data
        block[blkPos] = recvBuffer[0];
        // checksum all bytes modulo 256, tricky overflow
        sum += static_cast<uint8_t>(recvBuffer[0]);

        blkPos++;
        if (blkPos >= block.size()) {
          state = State::crc;
        }
        run = callback(State::data, blockNo, "");
        continue;
        break;

      case State::crc: {
        if (static_cast<uint8_t>(recvBuffer[0]) == sum) {
          run = callback(State::crc, blockNo, "");
          // checksum is OK, store to buffer

          if (!_ignoreBlockNmber && (lastBlockNo + 1) != blockNo) {
            throw exceptions::protocol_error("invalid sequnece block number");
          }

          lastBlockNo = blockNo;
          state = State::init;
          sendBuffer = ACK;
          rc += block;

        } else {
          // send block again
          state = State::init;
          sendBuffer = NAK;
          run = callback(State::crcErr, blockNo, "");
        }
        continue;
      } break;

      default: { // other types as init ...
        sendBuffer.clear();

        switch (recvBuffer[0]) {
        case SOH: // Start of Header, 128 bytes
          block.resize(128);
          blkPos = 0;
          state = State::blockNum;
          continue;
          break;
        case STX: // Start of Header, 1024 bytes
          block.resize(1024);
          blkPos = 0;
          continue;
          break;
        case EOT: // End of Transmission

          sendBuffer = ACK;
          state = State::end;
          continue;

          break;
        case CAN:
          run = callback(State::cancelled, blockNo, "");
          aetReceiver();
          sendBuffer = ACK;
          state = State::end;
          continue;
          break;
        default:
          break;
        }
      } break;
      }
    }
  }

  if (_stripPadding) {
    const auto strEnd = rc.find_last_not_of(_defPadding);
    rc = rc.substr(0, strEnd + 1);
  }

  return rc;
}

} // namespace fv

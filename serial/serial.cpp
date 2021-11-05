//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   serial.cpp
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30

#ifndef _WIN32
// MAC OS
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/signal.h>
#include <errno.h>
#include <paths.h>
#include <sysexits.h>
#include <termios.h>
#include <sys/param.h>
#include <sys/select.h>

#else
// Win32

#endif

#include "serial.h"
#include "exceptions.h"

#include "../utils/tmop.h"

namespace fv::serial {



std::unique_ptr<ISerial> ISerial::Factory::createUnique() {
  return std::make_unique<Serial>();
}

void Serial::clear() {
  _port.clear();
  _vid = 0;
  _pid = 0;
  _vendor.clear();
  _device.clear();
  _speed = BDSpeed::bd9600;
  _parity = Parity::none;
  _flowControl = FlowControl::none;
  _dataBits = DataBits::b8;
  _stopBits = StopBits::stop_1;
  _opened = false;
#ifndef _WIN32
  _fd = -1;
#else
#endif
}

void Serial::updateConfig() {
#ifndef _WIN32
  struct termios options;
  // get info from opened location
  if (tcgetattr(_fd, &options)) {
    throw exceptions::core_error("tcgetattr failed");
  }

  // enable receiver, ignore modem status line
  options.c_cflag |= (tcflag_t)(CREAD | CLOCAL);

  // term
  options.c_lflag &=
      (tcflag_t) ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ISIG | IEXTEN);

  // flow control
  switch (_flowControl) {
  case FlowControl::none:
    options.c_iflag &= (tcflag_t) ~(IXON | IXOFF | IXANY);
    options.c_cflag &= (unsigned long)~(CRTSCTS);
    break;
  case FlowControl::xonff:
    options.c_iflag |= (IXON | IXOFF);
    options.c_cflag &= (unsigned long)~(CRTSCTS);
    break;
  case FlowControl::hw:
    options.c_iflag &= (tcflag_t) ~(IXON | IXOFF | IXANY);
    options.c_cflag |= (CRTSCTS);
    break;
  defualt:
    break;
  }

  // This is a completely non-blocking read
  options.c_cc[VTIME] = 0;
  options.c_cc[VMIN] = 0;

  options.c_cflag &= (tcflag_t)~CSIZE;
  switch (_dataBits) {
  case DataBits::b5:
    options.c_cflag |= CS5;
    break;
  case DataBits::b6:
    options.c_cflag |= CS7;
    break;
  case DataBits::b7:
    options.c_cflag |= CS6;
    break;
  case DataBits::b8:
    options.c_cflag |= CS8;
    break;
  default:
    options.c_cflag |= CS8;
    break;
  }

  switch (_stopBits) {
  case StopBits::stop_1:
    options.c_cflag &= (tcflag_t) ~(CSTOPB);
    break;
  case StopBits::stop_1_5:
    options.c_cflag |= (CSTOPB);
    break;
  case StopBits::stop_2:
    options.c_cflag |= (CSTOPB);
    break;
  default:
    options.c_cflag &= (tcflag_t) ~(CSTOPB); // one bit
    break;
  }

  options.c_iflag &= (tcflag_t) ~(INPCK | ISTRIP);
  switch (_parity) {
  case Parity::none:
    options.c_cflag &= (tcflag_t) ~(PARENB | PARODD);
    break;
  case Parity::odd:
    options.c_cflag |= (PARENB | PARODD);
    break;
  case Parity::even:
    options.c_cflag &= (tcflag_t) ~(PARODD);
    options.c_cflag |= (PARENB);
    break;
  default:
    break;
  }

  // setup speed
  switch (_speed) {
  case BDSpeed::bd50:
    cfsetospeed(&options, B50);
    break;
  case BDSpeed::bd75:
    cfsetospeed(&options, B75);
    break;
  case BDSpeed::bd110:
    cfsetospeed(&options, B110);
    break;
  case BDSpeed::bd134:
    cfsetospeed(&options, B134);
    break;
  case BDSpeed::bd150:
    cfsetospeed(&options, B150);
    break;
  case BDSpeed::bd200:
    cfsetospeed(&options, B200);
    break;
  case BDSpeed::bd600:
    cfsetospeed(&options, B600);
    break;
  case BDSpeed::bd1200:
    cfsetospeed(&options, B1200);
    break;
  case BDSpeed::bd1800:
    cfsetospeed(&options, B1800);
    break;
  case BDSpeed::bd2400:
    cfsetospeed(&options, B2400);
    break;
  case BDSpeed::bd4800:
    cfsetospeed(&options, B4800);
    break;
  case BDSpeed::bd9600:
    cfsetospeed(&options, B9600);
    break;
  case BDSpeed::bd19200:
    cfsetospeed(&options, B19200);
    break;
  case BDSpeed::bd38400:
    cfsetospeed(&options, B38400);
    break;
  case BDSpeed::bd115200:
    cfsetospeed(&options, B115200);
    break;
  default:
    cfsetospeed(&options, B9600);
    break;
  }
  cfsetispeed(&options, cfgetospeed(&options));

  if (tcsetattr(_fd, TCSANOW, &options)) {
    throw exceptions::core_error("tcgetattr failed");
  }
#else

#endif
}

bool Serial::isOpen() const {
    return _opened;
}

void Serial::close() {
#ifndef _WIN32
  do {
    if (!_opened)
      break;
    if (_fd == -1)
      break;
    if (::close(_fd) != 0) {
      std::string err = "close failed error=";
      err += std::to_string(errno);
      throw exceptions::invalid_state(err.c_str());
    }
  } while (false);

  _fd = -1;
  _opened = false;
#else
#endif
}

void Serial::open() {

  if (_port.empty()) {
    throw exceptions::invalid_parameter("location is not set");
  }

  if (_opened) {
    throw exceptions::invalid_state("location already opened");
  }
#ifndef _WIN32
  _fd = ::open(_port.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);

  if (_fd == -1) {
    std::string err = "open failed error=";
    err += std::to_string(errno);
    throw exceptions::invalid_state(err.c_str());
  }
  updateConfig();
  _opened = true;
#else

#endif
}

uint64_t Serial::numberOfWaitingBytes() {
  uint64_t rc = 0;

  if (!_opened) {
    throw exceptions::invalid_state("location not opened");
  }

  if (ioctl(_fd, FIONREAD, &rc) == -1) {
    throw exceptions::invalid_state("ioctl faied");
  }

  return rc;
}

/*
void Serial::flush() {

    if (!_opened) {
        throw exceptions::invalid_state("location not opened");
    }

    auto cc = tcdrain(_fd);
    if (cc == 0) {

    }
    //tcflush (_fd, TCOFLUSH);
    //tcflush (_fd, TCIFLUSH);TCFLSH//tcflush
    //  tcdrain (_fd);
}
*/
void Serial::write(const std::string_view &data) {

  fd_set fds;
  auto written = 0;

  if (!_opened) {
    throw exceptions::invalid_state("location not opened");
  }

  // maximum timeout for reads first data block

  while (data.length() > written) {

    FD_ZERO(&fds);
    FD_SET(_fd, &fds);
    timespec tmx = fv::utils::TimeOp::msToTimeSpec(_timeout);

    auto desc = pselect(_fd + 1, NULL, &fds, NULL, &tmx, NULL);
    if (desc == 0) {
      throw exceptions::timeout("write timeout");
    } else if (desc < 0) {
      if (errno == EINTR) { // call in progress
        continue;
      }
      throw exceptions::invalid_state("pselect - failed");
    } else {
      if (FD_ISSET(_fd, &fds)) {

        auto donewritten =
            ::write(_fd, data.data() + written, data.length() - written);

        // call in progress
        if (errno == EINTR && donewritten == -1) {
          continue;
        }

        if (donewritten < 1) {
          throw exceptions::disconnected("location closed");
        }

        written += donewritten;

        if (donewritten >= data.length()) {
          break;
        }
      }
    }
  }
}

std::string Serial::read(size_t maxchars, size_t timeout) {
  std::string rc;
  fd_set fds;
    size_t cntread = 0;
    size_t retry = max_retry;

  if (!_opened) {
    throw exceptions::invalid_state("location not opened");
  }

  do {
    FD_ZERO(&fds);
    FD_SET(_fd, &fds);

    timespec tmx =
        fv::utils::TimeOp::msToTimeSpec((timeout == 0) ? _timeout : timeout);
    auto desc = pselect(_fd + 1, &fds, nullptr , nullptr, &tmx, nullptr);
    if (desc == 0) {
      throw exceptions::timeout("read timeout");
    } else if (desc < 0) {
      if (errno == EINTR) {
        // no data  -  select interrupted
        break;
      }
    }

    if (!FD_ISSET(_fd, &fds)) {
      throw exceptions::invalid_state("select failed");
    }

    rc.resize((maxchars == 0) ? 1024 : maxchars);
    do {
      cntread = ::read(_fd, &rc[0], rc.size());
      if (cntread < 0) {
        throw exceptions::timeout("read failed");
      }

      if (cntread > 0) {
        rc.resize(cntread);
      } else {
          retry --;
          if (cntread == 0 && retry==0) {
              rc.erase();
              break;
          }
      }
        
        
        
    } while (cntread == 0);

  } while (false);

  return rc;
}

} // namespace fv::serial

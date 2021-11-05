//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   serial.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30

#pragma once

#include "../include/serial_intf.h"
#include <string>
#include <sstream>
#include <memory>
#include <string_view>


namespace fv::serial {

class Serial : public ISerial {

private:
    std::string _port;
    uint16_t    _vid {0};
    uint16_t    _pid {0};
    std::string _vendor;
    std::string _device;
    BDSpeed     _speed {BDSpeed::bd9600};
    Parity      _parity {Parity::none};
    FlowControl _flowControl {FlowControl::none};
    DataBits    _dataBits {DataBits::b8};
    StopBits    _stopBits {StopBits::stop_1};
    bool        _opened {false};
    uint64_t    _timeout {1000};
    size_t max_retry =  10;
    
    
#ifndef _WIN32
    int         _fd {-1};   
#else
    
#endif
    
public:

    virtual void open() override;
    virtual void close() override;
    virtual bool isOpen() const override;
    virtual uint64_t  numberOfWaitingBytes() override;
    virtual std::string read(size_t maxchars, size_t timeout) override;
    virtual void write(const std::string_view& data) override;
   // virtual void flush() override;
    
    virtual void clear() override;
    virtual ISerial& withDeviceLocation(const std::string_view& port) override {
        _port = port;
        return *this;
    }
    
    virtual std::string getLocation() const override {
        return _port;
    }


    virtual ISerial& withTimeout(uint64_t tm) override {
        _timeout = tm;
        return *this;
    }
    
    virtual uint64_t getTimeout() const override {
        return _timeout;
    }
    
    virtual ISerial& withHWinfo(uint16_t vid, uint16_t pid) override {
        _vid = vid;
        _pid = pid;
        return *this;
    }
    
    virtual uint16_t getPID() const override {
        return _pid;
    }
    
    virtual uint16_t getVID() const override {
        return _vid;
    }


    virtual ISerial& withVendorName(const std::string_view& name) override {
        _vendor = name;
        return *this;
    }
    
    virtual std::string getVendorName() const override {
        return _vendor;
    }

    virtual ISerial& withDeviceName(const std::string_view& name) override {
        _device = name;
        return *this;
    }
    virtual std::string getDeviceName() const override {
        return _device;
    }
    
    virtual ISerial& withBdSpeed(BDSpeed speed) override {
        _speed = speed;
        return *this;
    }
    virtual BDSpeed getBdSpeed() const override {
        return _speed;
    }
   
    virtual ISerial& withParity(Parity par) override {
        _parity = par;
        return *this;
    }
    
    virtual Parity getParity() const override {
        return _parity;
    }

    virtual ISerial& withStopBits(StopBits bits) override {
        _stopBits = bits;
        return *this;
    }
    
    virtual StopBits getStiopBits() const override {
        return _stopBits;
    }

    virtual ISerial& withFlowControl(FlowControl flw) override {
        _flowControl = flw;
        return *this;
    }
    virtual FlowControl getFlowControl() const override {
        return _flowControl;
    }

    virtual ISerial& withDataBits(DataBits data) override {
        _dataBits = data;
        return *this;
    }
    
    virtual DataBits getDataBits() const override {
        return _dataBits;
    }
 
private:
    void updateConfig();
    
 /*
  virtual ~Serial ();

  void open ();

  bool isOpen () const;

  void close ();

  size_t available ();

  bool  waitReadable ();
void  waitByteTimes (size_t count);
  size_t  read (uint8_t *buffer, size_t size);
  size_t  read (std::vector<uint8_t> &buffer, size_t size = 1);
  size_t  read (std::string &buffer, size_t size = 1);

  std::string  read (size_t size = 1);

  size_t readline (std::string &buffer, size_t size = 65536, std::string eol = "\n");
  std::string readline (size_t size = 65536, std::string eol = "\n");

  std::vector<std::string> readlines (size_t size = 65536, std::string eol = "\n");

  size_t  write (const uint8_t *data, size_t size);

  size_t  write (const std::vector<uint8_t> &data);

  size_t  write (const std::string &data);

  void  setPort (const std::string &port);

  std::string  getPort () const;

  void
  setTimeout (Timeout &timeout);


  void
  setTimeout (uint32_t inter_byte_timeout, uint32_t read_timeout_constant,
              uint32_t read_timeout_multiplier, uint32_t write_timeout_constant,
              uint32_t write_timeout_multiplier)
  {
    Timeout timeout(inter_byte_timeout, read_timeout_constant,
                    read_timeout_multiplier, write_timeout_constant,
                    write_timeout_multiplier);
    return setTimeout(timeout);
  }

  Timeout
  getTimeout () const;

  void
  setBaudrate (uint32_t baudrate);

  uint32_t
  getBaudrate () const;

  void
  setBytesize (bytesize_t bytesize);

    bytesize_t
  getBytesize () const;

  void
  setParity (parity_t parity);

    parity_t
  getParity () const;

  void
  setStopbits (stopbits_t stopbits);

    stopbits_t
  getStopbits () const;

  
    void
  setFlowcontrol (flowcontrol_t flowcontrol);

  
    flowcontrol_t
  getFlowcontrol () const;

  void
  flush ();

  void
  flushInput ();

  void
  flushOutput ();

  void
  sendBreak (int duration);

  void
  setBreak (bool level = true);

  void
  setRTS (bool level = true);

  void
  setDTR (bool level = true);

  
  bool
  waitForChange ();

  bool
  getCTS ();

  bool
  getDSR ();

  bool
  getRI ();

  bool
  getCD ();

private:
  // Disable copy constructors
  Serial(const Serial&);
  Serial& operator=(const Serial&);

  // Pimpl idiom, d_pointer
  class SerialImpl;
  SerialImpl *pimpl_;

  // Scoped Lock Classes
  class ScopedReadLock;
  class ScopedWriteLock;

  size_t
  read_ (uint8_t *buffer, size_t size);
  size_t
  write_ (const uint8_t *data, size_t length);
*/
};


}

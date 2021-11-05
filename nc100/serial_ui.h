//
//  serial_ui.h
//  nc100
//
//  Created by Petr Vanek on 10.09.2021.
//

#pragma once
#include "../include/serial_intf.h"
#include "../include/serial_enumerator_intf.h"
#include "../include/cli_ui.h"
#include <iostream>

namespace fv::ui {

template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

struct Cfg{
    serial::BDSpeed     _speedS {serial::BDSpeed::bd9600} ;
    serial::DataBits    _bitsS {serial::DataBits::b8} ;
    serial::FlowControl _flowS {serial::FlowControl::none};
    serial::Parity      _parityS {serial::Parity::none};
    serial::StopBits    _stopsS {serial::StopBits::stop_1};
};


void printSerials( serial::t_vector_serial const& vser, bool onlyWithPID);
  
serial::BDSpeed getSerialSepeed() ;

serial::DataBits getSerialBits() ;

serial::FlowControl getFlow() ;

serial::Parity getParity() ;

serial::StopBits getStopBits();

void shwoSerialSetting(const Cfg& cfg);

}

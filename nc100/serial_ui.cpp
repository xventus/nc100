//
//  serial_ui.hpp
//  nc100
//
//  Created by Petr Vanek on 10.09.2021.
//



#include "serial_ui.h"
#include <vector>

namespace fv::ui {
//------------------------------------------------------------------------------------------------------------------
void printSerials(fv::serial::t_vector_serial const &vser,
                       bool onlyWithPID) {

  std::cout << std::endl;
  std::cout << "Position  Device                         " << std::endl;
  auto pos = 0;
  for (const auto &it : vser) {
    std::cout << pos++ << ".        " << it->getLocation();
    if (!it->getDeviceName().empty()) {
      std::cout << "      \t[" << it->getDeviceName() << "]";
    }

    std::cout << std::endl;
  }
}

//------------------------------------------------------------------------------------------------------------------

void shwoSerialSetting(const Cfg& cfg) {
   tcout <<   as_integer(cfg._speedS) << "/" <<   as_integer(cfg._bitsS) << "-";
   switch(cfg._parityS) {
        case fv::serial::Parity::none:   tcout <<  TEXT("N-"); break;
        case fv::serial::Parity::odd:    tcout <<  TEXT("O-"); break;
        case fv::serial::Parity::even:   tcout <<  TEXT("E-"); break;
   }
    switch(cfg._stopsS) {
         case fv::serial::StopBits::stop_1:   tcout <<  TEXT("1"); break;
         case fv::serial::StopBits::stop_1_5: tcout <<  TEXT("1.5"); break;
         case fv::serial::StopBits::stop_2:   tcout <<  TEXT("2"); break;
    }
    tcout << TEXT("\n");
}

//------------------------------------------------------------------------------------------------------------------
fv::serial::BDSpeed getSerialSepeed() {
  tcout << TEXT("\n\n== Available speed ==\n\n");
    auto v = 0;
    for (const auto &i : fv::serial::all_speeds) {
        tcout << v++ << ".\t\t\t" << static_cast<int>(i) << "\n";
    }
    auto val =  fv::ui::inputInteger(TEXT("select position:"), 12, 0,fv::serial::all_speeds.size());
    return fv::serial::all_speeds[val];
}
//------------------------------------------------------------------------------------------------------------------

fv::serial::DataBits getSerialBits() {
    tcout << TEXT("\n\n== Number of data bits ==\n\n");
    auto v = 0;
    for (const auto &i : fv::serial::all_bits) {
        tcout << v++ << ".\t\t\t" << static_cast<int>(i) << " bits\n";
    }
    auto val =  fv::ui::inputInteger(TEXT("select position:"), 3, 0,fv::serial::all_bits.size());
    return fv::serial::all_bits[val];
}

//------------------------------------------------------------------------------------------------------------------

fv::serial::FlowControl getFlow() {
    auto rc = fv::serial::FlowControl::none;
    tcout << TEXT("\n\n== Flow control ==\n\n");
     
    tcout << 0 << ".   none \n";
    tcout << 1 << ".   xon/xoff \n";
    tcout << 2 << ".   hardware \n";
    auto val =  fv::ui::inputInteger(TEXT("select position:"), 0, 0,2);
    switch (val) {
        case 0 : rc = fv::serial::FlowControl::none; break;
        case 1 : rc = fv::serial::FlowControl::xonff; break;
        case 2 : rc = fv::serial::FlowControl::hw; break;
        default: rc = fv::serial::FlowControl::none; break;
    }
    
    return rc;
}

//------------------------------------------------------------------------------------------------------------------

fv::serial::Parity getParity() {
    auto rc = fv::serial::Parity::none;
    tcout << TEXT("\n\n== Flow control ==\n\n");
     
    tcout << 0 << ".   none \n";
    tcout << 1 << ".   odd \n";
    tcout << 2 << ".   even \n";
    auto val =  fv::ui::inputInteger(TEXT("select position:"), 0, 0,2);
    switch (val) {
        case 0 : rc = fv::serial::Parity::none; break;
        case 1 : rc = fv::serial::Parity::odd; break;
        case 2 : rc = fv::serial::Parity::even; break;
        default: rc = fv::serial::Parity::none; break;
    }
    
    return rc;
}


//------------------------------------------------------------------------------------------------------------------

fv::serial::StopBits getStopBits() {
    auto rc = fv::serial::StopBits::stop_1;
    tcout << TEXT("\n\n== Stop bits ==\n\n");
     
    tcout << 0 << ".   1 bit \n";
    tcout << 1 << ".   1.5 bit \n";
    tcout << 2 << ".   2 bits \n";
    auto val =  fv::ui::inputInteger(TEXT("select position:"), 0, 0,2);
    switch (val) {
        case 0 : rc = fv::serial::StopBits::stop_1; break;
        case 1 : rc = fv::serial::StopBits::stop_1_5; break;
        case 2 : rc = fv::serial::StopBits::stop_2; break;
        default: rc = fv::serial::StopBits::stop_1; break;
    }
    
    return rc;
}
}

//
//  application.hpp
//  nc100
//
//  Created by Petr Vanek on 10.09.2021.
//

#pragma once
#include "../include/cli_ui.h"
#include "../include/serial_enumerator_intf.h"
#include <algorithm>
#include <stdio.h>
#include <string>
#include <list>
#include <variant>
#include <any>

namespace fv::ui {

// --------------------------------------------------------------------------------------------------
class App : public IApplication {

  //  using Params = std::vector<std::variant<std::string, int32_t>>;

private:
public:
  typedef void (App::*t_fn_action)();

  App();
    
     virtual int wmain(int argc, const TCHAR *argv[]);

  void none();

private:
  static void f_serialList(std::any &param);

  static void f_setSerialSpeed(std::any &param);
  static void f_setSerialBits(std::any &param);
  static void f_setSerialStop(std::any &param);
  static void f_setSerialParity(std::any &param);
  static void f_setSerialFlow(std::any &param);
  static void f_showParams(std::any &param);
  static void f_receiver(std::any &param);
  static void f_xreceiver(std::any &param);
  static void f_xsender(std::any &param);
  static std::unique_ptr<serial::ISerial> getPort();
};
// --------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------

} // namespace fv::ui

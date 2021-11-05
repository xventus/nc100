//
//  application.cpp
//  nc100
//
//  Created by Petr Vanek on 10.09.2021.
//

#include "application.h"

#include "../include/menu_ui.h"
#include "../include/hex_stream_formatter.h"
#include "../include/crc.h"
#include "../include/modem.h"
#include "serial_ui.h"

namespace fv::ui {

template <typename Bench> void call_no_exception(Bench f) {
  try {
    f();
  } catch (const exceptions::all &ex) {
    tcout << TEXT("exception, reason: ") << ex.what() << TEXT("\n");

  } catch (const std::exception &ex) {
    tcout << TEXT("exception, reason: ") << ex.what() << TEXT("\n");
  } catch (...) {
    tcout << TEXT("unknown exception") << TEXT("\n");
  }
}

std::unique_ptr<IApplication> IApplication::Factory::createInstance() {
  return std::make_unique<App>();
}

//------------------------------------------------------------------------------------------------------------------

App::App() {}

//------------------------------------------------------------------------------------------------------------------

void App::f_serialList(std::any &param) {
  tcout << TEXT("\n\nAvailable serial ports\n");
  fv::ui::ConsoleMenu menuSerialSelector;
  auto enumerator = fv::serial::ISerialEnumerator::Factory::createUnique();
  auto eports = enumerator->scan();
  fv::ui::printSerials(eports, false);
}

//------------------------------------------------------------------------------------------------------------------

void App::f_setSerialSpeed(std::any &param) {
  auto x = std::any_cast<Cfg>(param);
  x._speedS = ui::getSerialSepeed();
}

void App::f_setSerialBits(std::any &param) {
  auto x = std::any_cast<Cfg>(param);
  x._bitsS = ui::getSerialBits();
}

void App::f_setSerialStop(std::any &param) {
  auto x = std::any_cast<Cfg>(param);
  x._stopsS = ui::getStopBits();
}

void App::f_setSerialParity(std::any &param) {
  auto x = std::any_cast<Cfg>(param);
  x._parityS = ui::getParity();
}

void App::f_setSerialFlow(std::any &param) {
  auto x = std::any_cast<Cfg>(param);
  x._flowS = ui::getFlow();
}

void App::f_showParams(std::any &param) {
  tcout << TEXT("\n\nActual setting: ");
  ui::shwoSerialSetting(std::any_cast<Cfg>(param));
}

void f_none(std::any &param) {}

void App::f_xsender(std::any &param) {
  call_no_exception([&] {
    auto x = std::any_cast<Cfg>(param);
    auto port = getPort();
    if (port) {
      port->withParity(x._parityS)
          .withBdSpeed(x._speedS)
          .withStopBits(x._stopsS)
          .withDataBits(x._bitsS)
          .withFlowControl(serial::FlowControl::hw);
    }

     auto data =  inputUTF8String(TEXT("Text to send:"), "0123456789END", 0);
     
    fv::Modem modem(std::move(port));
    modem.addCallback([](auto s, auto p, auto data) {
        if (s == Modem::State::init) {
            tcout << TEXT("\nInit: ") << p << TEXT(" ");
        } else if (s ==  Modem::State::timeouted) {
            tcout << TEXT("\ntimouted! ") << p << TEXT(" ");
            return false; // stop after timeout !!!
        }
        else  if (s == Modem::State::blockNumErr) {
            tcout << TEXT("\nError Block: ") << p << TEXT(" ");
        } else if (s == Modem::State::blockNum) {
        tcout << TEXT("\nBlock: ") << p << TEXT(" ");
      } else if (s == Modem::State::data) {
        tcout << TEXT(".");
      } else if (s == Modem::State::end) {
        tcout << TEXT("\nDone\n");
      }
      return true;
    });

    modem.open();
    modem.X128Send(data);
    
    if (modem.isOpened())
    modem.close();

  });
}

void App::f_xreceiver(std::any &param) {
  call_no_exception([&] {
    auto x = std::any_cast<Cfg>(param);
    auto port = getPort();
    if (port) {
      port->withParity(x._parityS)
          .withBdSpeed(x._speedS)
          .withStopBits(x._stopsS)
          .withDataBits(x._bitsS)
          .withFlowControl(serial::FlowControl::hw);
    }

    fv::ui::pressAnyKey(
        "Start the transfer on the remote device and press any key.");
    fv::Modem modem(std::move(port));
    modem.addCallback([](auto s, auto p, auto data) {
      if (s == Modem::State::blockNum) {
        tcout << TEXT("\nBlock: ") << p << TEXT(" ");
      } else if (s == Modem::State::data) {
        tcout << TEXT(".");
      } else if (s == Modem::State::end) {
        tcout << TEXT("\nDone\n");
      }

      return true;
    });

    modem.open();
    auto msg = modem.X128Receive();
    if (modem.isOpened())
      modem.close();

    std::cout << fv::utils::HexDumper<const std::vector<uint8_t>>(
        {msg.begin(), msg.end()}, 16);
  });
}

void App::f_receiver(std::any &param) {
  call_no_exception([&] {
    std::string message;
    auto x = std::any_cast<Cfg>(param);
    size_t cnt = 0;
    auto port = getPort();
    bool termchar = false;

    if (port) {
      auto echo = askYesNo(TEXT("echo"), false);
      auto maxchars = fv::ui::inputInteger(
          TEXT("terminate after number of chars:"), 64, 1, 1024);
      auto terminateChar =
          fv::ui::inputInteger(TEXT("terminate char  DEC:"), 26, 0, 255);
      auto printafter =
          fv::ui::inputInteger(TEXT("print after chars:"), 8, 1, 255);

      port->withParity(x._parityS)
          .withBdSpeed(x._speedS)
          .withStopBits(x._stopsS)
          .withDataBits(x._bitsS);

      do {
        port->open();
        while (true) {
          auto x = port->read(1);
          if (!x.empty()) {

            if (x.find(terminateChar) != std::string::npos) {
              termchar = true;
            }

            message += x;
            // display dump
            if (termchar || message.length() >= printafter) {
              std::cout << fv::utils::HexDumper<const std::vector<uint8_t>>(
                  {message.begin(), message.end()}, printafter);
              //  << std::endl;
              message.clear();
            }

            // echo back to sender
            if (echo) {
              port->write(x);
            }

            if (termchar) {
              std::cout << "Terminate char received" << std::endl;
              break;
            }

            // receiver counter
            cnt += x.size();
            if (cnt >= maxchars) {
              break;
            }
          }
        }

        port->close();

        if (!askYesNo(TEXT("run again?"), true)) {
          break;
        }

        cnt = 0;
        termchar = false;

      } while (true);
    }
  });
  ;
}

std::unique_ptr<serial::ISerial> App::getPort() {
  tcout << TEXT("\n\nAvailable serial ports\n");
  fv::ui::ConsoleMenu menuSerialSelector;
  auto enumerator = fv::serial::ISerialEnumerator::Factory::createUnique();
  auto eports = enumerator->scan();
  if (eports.empty()) {
    tcout << TEXT("\n\nPort not found\n");
    return nullptr;
  }

  fv::ui::printSerials(eports, false);
  auto val =
      fv::ui::inputInteger(TEXT("select position:"), 0, 0, eports.size());
  return std::move(eports[val]);
}


//------------------------------------------------------------------------------------------------------------------

int App::wmain(int argc, const TCHAR *argv[]) {

  int exitCode = 0;

  fv::ui::ConsoleMenu serialParamMenu{
      "Serial Parametters",
      {{'s', "Speed", f_setSerialSpeed},
       {'b', "Data bits", f_setSerialBits},
       {'d', "Stop bits", f_setSerialStop},
       {'p', "Parity", f_setSerialParity},
       {'f', "Flow controll", f_setSerialFlow}}};

  fv::ui::ConsoleMenu mainMenu{
      "main menu",
      {

          {'i', "serial info", f_showParams},
          {'l', "list of serial port", f_serialList},
          {'c', "simple receiver", f_receiver},
          {'r', "x-modem receiver", f_xreceiver},
          {'x', "x-modem sender", f_xsender},
          {'s', "set default params ", &serialParamMenu},
         
      }};

  // config params
  std::any param = Cfg{};

  mainMenu.run(param);
  std::cout << std::endl;
  std::cout << "Bye. " << std::endl;

  return exitCode;
}
} // namespace fv::ui

//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   cli_ui.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-01-20

#pragma once

#include "crosstypes.h"
#include <string>
#include <memory>
#include <functional>
#include <string>
#include <algorithm>
#include <unistd.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#endif

namespace fv::ui {

//------------------------------------------------------------------------------------------------------------------

class IApplication {
public:
  virtual ~IApplication() = default;

  virtual int wmain(int argc, const TCHAR *argv[]) = 0;

  struct Factory {
    static std::unique_ptr<IApplication> createInstance();
  };
};

//------------------------------------------------------------------------------------------------------------------
//   terminal functions
//------------------------------------------------------------------------------------------------------------------

/// Display prompt to enter a string.
/// @param prompt Prompt message.
/// @param defInput Default value that is used if the user just pressed Enter.
/// This parameter can be nullptr.
/// @param fixLen required fixed length of the input string. This parameter is
/// ignored if the value is 0.
/// @return String input.
t_tstr inputString(const TCHAR *prompt, const TCHAR *defInput = nullptr,
                   size_t fixLen = 0);

/// Display prompt to enter a string.
/// @param prompt Prompt message.
/// @param defInput Default value that is used if the user just pressed Enter.
/// This parameter can be nullptr.
/// @param fixLen required fixed length of the input string. This parameter is
/// ignored if the value is 0.
/// @return UTF-8 encoded string input.
std::string inputUTF8String(const TCHAR *prompt, const char *defInput = nullptr,
                            size_t fixLen = 0);

/// Display prompt to enter a secret string. The predefined character is
/// displayed instead of each input character.
/// @param prompt Prompt message.
/// @param defInput Default value that is used if the user just pressed Enter.
/// @param fixLen required fixed length of the input string. This parameter is
/// ignored if the value is 0.
/// @return UTF-8 encoded string input.
std::string inputSecret(const TCHAR *prompt, const char *defInput = nullptr,
                        size_t fixLen = 0);

/// Display prompt to enter an integer value.
/// @param prompt Prompt message.
/// @param defInput Default value that is used if the user just pressed Enter.
/// @param min Lowest acceptable value. This parameter is ignored if its value
/// matches the max parameter.
/// @param max Highest acceptable value. This parameter is ignored if its value
/// matches the min parameter.
/// @return Integer value.
int64_t inputInteger(const TCHAR *prompt, int64_t defInput = 0, int64_t min = 0,
                     int64_t max = 0);

///
/// @param prompt Prompt message.
/// @param defaultYes Default answer that is used if the user just pressed
/// Enter.
/// @return True if the answer is "Yes" or false otherwise.
bool askYesNo(const TCHAR *prompt, bool defaultYes = true);

/*
  std::wstring inputString(const std::wstring &prompt,
                           const std::wstring &defInput, size_t fixLen) {
    std::wstring input;

    for (;;) {

      std::wcout << prompt.c_str();
      if (!defInput.empty()) {
        std::wcout << L" [" << defInput.c_str() << L"]";
      }
      std::wcout << L": ";
      std::getline(std::wcin, input);

      if (input.empty() && !defInput.empty()) {
        input = defInput;
      }

      if ((fixLen != 0) && (input.length() != fixLen)) {
        std::wcout << L"Invalid length of input. Length is " << input.length()
                   << L" characters, input should be " << fixLen
                   << L" characters long." << std::endl;
        continue;
      }

      break; // <- success
    }

    return input;
  }
*/

//------------------------------------------------------------------------------------------------------------------

static int x__getche() {
#ifdef _WIN32
  return getche();
#else
  int ch;
  struct termios old, tios;

  tcgetattr(0, &old);
  tios = old;
  tios.c_lflag &= ~ICANON; // disable buffered IO
  tios.c_lflag &= ECHO;    // echo mode
  tcsetattr(0, TCSANOW, &tios);
  ch = getchar();
  tcsetattr(0, TCSANOW, &old);

  return ch;
#endif
}

//------------------------------------------------------------------------------------------------------------------

static int x__getch() {
#ifdef _WIN32
  return getch();
#else
  int ch;
  struct termios old, tios;

  tcgetattr(0, &old);
  tios = old;
  tios.c_lflag &= ~ICANON; // disable buffered IO
  tios.c_lflag &= ~ECHO;   // echo mode
  tcsetattr(0, TCSANOW, &tios);
  ch = getchar();
  tcsetattr(0, TCSANOW, &old);

  return ch;
#endif
}

//------------------------------------------------------------------------------------------------------------------

static void pressAnyKey(const std::string_view& msg = "Press any key...") {
  tcout << msg << std::endl;
  x__getch();
}

} // namespace fv::ui

//------------------------------------------------------------------------------------------------------------------
//  Formating classes
//------------------------------------------------------------------------------------------------------------------

/// Insert binary data formated as hexadecimal string into output stream.
class UUID {
private:
  const uint8_t *_bin;
  size_t _len;

public:
  UUID(const std::string &bin)
      : _bin((uint8_t *)bin.data()), _len(bin.size()) {}
  friend tostream &operator<<(tostream &os, const UUID &tx);
};

//------------------------------------------------------------------------------------------------------------------

/// Insert formated ID into output stream.
class HEX {
private:
  const uint8_t *_bin;
  size_t _len;

public:
  HEX(const std::string &bin) : _bin((uint8_t *)bin.data()), _len(bin.size()) {}
  friend tostream &operator<<(tostream &os, const HEX &tx);
};

//------------------------------------------------------------------------------------------------------------------

/// Insert UTF-8 formated string into output stream.
class UTF8 {
private:
  std::string_view _str;
  const TCHAR *_estr;

public:
  UTF8(std::string_view str, const TCHAR *estr = nullptr)
      : _str(str), _estr(estr) {}
  friend tostream &operator<<(tostream &os, const UTF8 &tx);
};

//------------------------------------------------------------------------------------------------------------------

class YesNo {
private:
  bool _b;
  const TCHAR *_yes;
  const TCHAR *_no;

public:
  YesNo(bool b, const TCHAR *y = nullptr, const TCHAR *n = nullptr)
      : _b(b), _yes(y), _no(n) {}
  friend tostream &operator<<(tostream &os, const YesNo &tx);
};

//------------------------------------------------------------------------------------------------------------------

/// Insert standardized timestamp for log.
class logTime {
private:
  int64_t _t;

public:
  logTime(int64_t t) : _t(t) {}
  friend tostream &operator<<(tostream &os, const logTime &tx);
};

class printUnknownException {
public:
  printUnknownException() = default;
  friend tostream &operator<<(tostream &os, const printUnknownException &tx);
};

//------------------------------------------------------------------------------------------------------------------

class printStdException {
private:
  const std::exception &_ex;

public:
  printStdException(const std::exception &ex) : _ex(ex) {}
  friend tostream &operator<<(tostream &os, const printStdException &tx);
};

//------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------

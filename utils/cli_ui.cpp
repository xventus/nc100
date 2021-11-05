//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   cli_ui.cpp
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-01-20

#include "cli_ui.h"
#include <iomanip>
#include "../utils/strop.h"

namespace fv::ui {

bool input_echo(bool enable) {
  bool prev = true;
#ifdef WIN32
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD mode;
  GetConsoleMode(hStdin, &mode);
  prev = (mode & ENABLE_ECHO_INPUT) == ENABLE_ECHO_INPUT;
  if (enable) {
    mode |= ENABLE_ECHO_INPUT;
  } else {
    mode &= ~ENABLE_ECHO_INPUT;
  }
  SetConsoleMode(hStdin, mode);
#else
  struct termios tty;
    if (tcgetattr(STDIN_FILENO, &tty)) {
        ;
    }
  prev = (tty.c_lflag & ECHO) == ECHO;
  if (enable) {
    tty.c_lflag |= ECHO;
  } else {
    tty.c_lflag &= ~ECHO;
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
  return prev;
}

class input_echo_with_reset {
private:
  bool _prev;

public:
  input_echo_with_reset(bool echo) { _prev = input_echo(echo); }
  virtual ~input_echo_with_reset() { input_echo(_prev); }
};

t_tstr promptForInput(const TCHAR *prompt, t_tstr &input,
                      const TCHAR *defInput = nullptr, size_t fixLen = 0,
                      bool secret = false) {
  assert(prompt != nullptr);

  input_echo_with_reset echo(!secret);

  for (;;) {

    // prompt
    tcout << prompt;
    if (defInput && *defInput) {
      tcout << TEXT(" [");
      for (const TCHAR *d = defInput; *d; ++d) {
        if (secret) {
          tcout << TEXT('*');
        } else {
          tcout << *d;
        }
      }
      tcout << TEXT("]");
    }
    tcout << TEXT(": ");

    // input reading
    std::getline(tcin, input);
    if (secret) {
      tcout << TEXT("\n");
    }

    // input validation
    if (input.empty() && defInput) {
      input = defInput;
    } else if (input.compare(TEXT("0nic")) == 0) {
      input.clear();
    }
    if ((fixLen == 0) || (input.length() == fixLen)) {
      break; // <- success
    }
    tcout << TEXT("Invalid length of input. Length is ") << input.length()
          << TEXT(" character(s), input should be ") << fixLen
          << TEXT(" character(s) long.\n");
  }

  return input;
}

t_tstr inputString(const TCHAR *prompt, const TCHAR *defInput, size_t fixLen) {
  t_tstr input;
  fv::ui::promptForInput(prompt, input, defInput, fixLen);
  return input;
}

std::string inputUTF8String(const TCHAR *prompt, const char *defInput,
                            size_t fixLen) {
  t_tstr input;
  if (defInput) {
    fv::ui::promptForInput(prompt, input,
                           fv::utils::StrOp::utf82t(defInput).c_str(), fixLen);
  } else {
    fv::ui::promptForInput(prompt, input, nullptr, fixLen);
  }
  return fv::utils::StrOp::t2utf8(input);
}

std::string inputSecret(const TCHAR *prompt, const char *defInput,
                        size_t fixLen) {
  t_tstr input;
  if (defInput) {
    fv::ui::promptForInput(prompt, input,
                           fv::utils::StrOp::utf82t(defInput).c_str(), fixLen,
                           true);
  } else {
    fv::ui::promptForInput(prompt, input, nullptr, fixLen, true);
  }
  return fv::utils::StrOp::t2utf8(input);
}

int64_t inputInteger(const TCHAR *prompt, int64_t defInput, int64_t min,
                     int64_t max) {

  int64_t number;

  for (;;) {

    const t_tstr &input = inputString(prompt, to_tstring(defInput).c_str(), 0);

    if (input.empty()) {
      number = defInput;
    } else {
      t_sstream inStream(input);
      if (!(inStream >> number)) {
        tcout << TEXT("Not a number, please try again.\n");
        continue;
      }
    }

    if ((min == max) || ((number >= min) && (number <= max))) {
      break; // <- success
    }

    tcout << TEXT("Number ") << number << TEXT(" is out of range [") << min
          << TEXT(" ... ") << max << TEXT("], please try again.\n");
  }

  return number;
}

bool matchStringNoCaseShorter(const TCHAR *shorter, const TCHAR *pattern) {
  assert(shorter != nullptr);
  assert(pattern != nullptr);

  bool match = false;

  if (*shorter) {
    while (*shorter && *pattern) {
      if ((*shorter != *pattern) &&
          (::tolower(*shorter) != ::tolower(*pattern))) {
        break;
      }
      ++shorter;
      ++pattern;
    }
    match = !*shorter;
  }

  return match;
}

bool askYesNo(const TCHAR *prompt, bool defaultYes) {

  const TCHAR *ANSWER_YES = TEXT("Yes");
  const TCHAR *ANSWER_NO = TEXT("No");

  bool yes = defaultYes;

  for (;;) {

    const t_tstr &ans =
        inputString(prompt, defaultYes ? ANSWER_YES : ANSWER_NO, 0);

    if (matchStringNoCaseShorter(ans.c_str(), ANSWER_YES)) {
      yes = true;
      break;
    }

    if (matchStringNoCaseShorter(ans.c_str(), ANSWER_NO)) {
      yes = false;
      break;
    }
  }

  return yes;
}

} // namespace fv::ui

// UUID -> ostream
tostream &operator<<(tostream &os, const UUID &tx) {

  if (tx._len == 0) {
    os << TEXT("<none>");
  } else {

    bool uuid = tx._len == 16;
    uint8_t num;

    for (size_t i = 0; i < tx._len; ++i) {

      if (uuid) {
        switch (i) {
        case 4:
        case 6:
        case 8:
        case 10:
          os << TEXT('-');
          break;
        }
      }

      num = (tx._bin[i] >> 4) & 0x0f;
      if (num <= 9)
        os << (char)('0' + num);
      else
        os << (char)('a' + (num - 10));

      num = (tx._bin[i] & 0x0f);
      if (num <= 9)
        os << (char)('0' + num);
      else
        os << (char)('a' + (num - 10));
    }
  }

  return os;
}

// HEX -> ostream
tostream &operator<<(tostream &os, const HEX &tx) {

  uint8_t num;

  for (size_t i = 0; i < tx._len; ++i) {
    num = (tx._bin[i] >> 4) & 0x0f;
    if (num <= 9)
      os << (char)('0' + num);
    else
      os << (char)('a' + (num - 10));

    num = (tx._bin[i] & 0x0f);
    if (num <= 9)
      os << (char)('0' + num);
    else
      os << (char)('a' + (num - 10));
  }

  return os;
}

// UTF8 -> ostream
// UTF8 -> ostream
tostream &operator<<(tostream &os, const UTF8 &tx) {
#ifdef _WIN32
  if (!tx._str.empty()) {
    os << utf8_to_t(tx._str).c_str();
  } else if (tx._estr) {
    os << tx._estr;
  }
#else
  if (*tx._str.data()) {
    os << tx._str; // NOTE for !Windows expect UTF-8 as native encoding
  } else if (tx._estr) {
    os << tx._estr;
  }
#endif
  return os;
}

// yes/no -> ostream
tostream &operator<<(tostream &os, const YesNo &tx) {
  if (tx._b) {
    os << (tx._yes ? tx._yes : TEXT("yes"));
  } else {
    os << (tx._no ? tx._no : TEXT("no"));
  }
  return os;
}

// log timestamp -> ostream
tostream &operator<<(tostream &os, const logTime &tx) {
  time_t nix = tx._t / 1000;
  os << std::put_time(std::localtime(&nix), TEXT("%F %T")); // TODO .msec
  return os;
}


// unknown exception -> osteam
tostream &operator<<(tostream &os, const printUnknownException &tx) {
  os << TEXT(">>>>>\n");
  os << TEXT("> Caught an unknown exception.\n");
  os << TEXT("<<<<<\n");
  return os;
}

// std::exception -> ostream
tostream &operator<<(tostream &os, const printStdException &tx) {
  os << TEXT(">>>>>\n");
  os << TEXT("> Caught exception: ") << tx._ex.what() << TEXT("\n");
  os << TEXT("<<<<<\n");
  return os;
}

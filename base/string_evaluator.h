
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   strop.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-10-05

#pragma once

#include <string>
#include <sstream>
#include <vector>
namespace fv::utils {

class StringEvaluator {

private:
  std::string _before;
  std::string _after;
  uint32_t _numberOfParam;
  vectStrIns_t _splitted;

public:
    StringEvaluator(uint32_t numberOfParam = 2,
                 const std::string_view before = "{",
                 const std::string_view after = "}")
      : _numberOfParam(numberOfParam), _before(before), _after(after) {}

  void process(const std::string_view &str) {
    _splitted.clear();

    std::string fr = find(str, 0);
    for (auto i = 1; i < _numberOfParam; i++) {
      fr = find(fr, i);
    }

    _splitted.push_back(tupleStrIns_t(-1, fr));
  }

  template <typename... Args> std::string evaluate(Args &&... args) {
    static_assert((std::is_constructible_v<std::string_view, Args &&> && ...));

    std::array arguments = {args...};
    std::string rc;

    size_t reserve = (std::string_view{args}.size() + ...);
    std::for_each(_splitted.cbegin(), _splitted.cend(), [&](auto &s) {
      reserve += std::get<std::string>(s).length();
    });
    rc.reserve(reserve);

    for (const auto &part : _splitted) {
      auto argumentNumber = std::get<int>(part);
      if (argumentNumber == -1) {
        // without any argument, only text
        rc += std::get<std::string>(part);
      }   else if (arguments.size() > static_cast<size_t>(std::get<int>(part))) {
      //} else if (arguments.size() > std::get<int>(part)) {
        rc += std::get<std::string>(part);
        rc += arguments[std::get<int>(part)];
      }
    }

    return rc;
  }

private:
  std::string find(const std::string_view &str, int32_t num) {

    size_t start = 0U;

    std::string delimiter = _before;
    delimiter += std::to_string(num);
    delimiter += _after;

    auto end = str.find(delimiter);
    while (end != std::string::npos) {
      auto part = str.substr(start, end - start);

      if (num < _numberOfParam) {
        // find in reverse
        auto r = find(part, num + 1);
        for (auto xnum = num + 2; xnum < _numberOfParam; xnum++) {
          r = find(r, xnum);
        }

        _splitted.push_back(tupleStrIns_t(num, r));
      }

      start = end + delimiter.length();
      end = str.find(delimiter, start);
    }

    return std::string(str.substr(start, end));
  }
};


}

//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   strop.cpp
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30

#include  "strop.h"
#include <regex>
#include <random>

namespace fv::utils {

std::vector<uint8_t> StrOp::getRawDataFromHex(const std::string &instr) {
                
    size_t len = instr.length();
    std::vector<uint8_t>  out;
    for(std::size_t i = 0; i < len; i += 2) {
        std::istringstream strm(instr.substr(i, 2));
        uint32_t x;
        strm >> std::hex >> x;
        out.push_back((unsigned char)x);
    }
    return out;
}

        
std::string_view StrOp::trim(std::string_view str, const std::string& chars)  {
  
    str.remove_prefix(std::min(str.find_first_not_of(chars), str.size()));
    str.remove_suffix(str.size() - str.find_last_not_of(chars) - 1);
    return str;
}

// tolower
std::string StrOp::toLower(const std::string_view& instr) {
    std::string outstr;
    outstr.resize(instr.length());
    std::transform(instr.begin(), instr.end(), outstr.begin(), ::tolower);
    return outstr;
}

std::vector<std::string>  StrOp::resplit(const std::string & s, std::string rgxs) {

    std::vector<std::string> e;
    std::regex rgx (rgxs);

    std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
    std::sregex_token_iterator end;

    while (iter != end)  {
        e.push_back(*iter);
        ++iter;
    }

    return e;
}


std::string StrOp::randomNumber(std::size_t length) {
   const std::string charbase = "0123456789";

   std::random_device random_device;
   std::mt19937 generator(random_device());
   std::uniform_int_distribution<> distribution(0, (int) charbase.size() - 1);

   std::string random_string;

   for (std::size_t i = 0; i < length; ++i)
   {
       random_string += charbase[distribution(generator)];
   }

   return random_string;
}


} // namespace 

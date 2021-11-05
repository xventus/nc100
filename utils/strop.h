//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   strop.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30

#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace fv::utils {

class  StrOp {
  
public:
    static std::vector<uint8_t> getRawDataFromHex(const std::string &instr);
    
    static std::string_view trim(std::string_view str, const std::string& chars = "\t\n\v\f\r ");
        
    static std::string toLower(const std::string_view& instr);
    
    static std::vector<std::string>  resplit(const std::string & s, std::string rgx_str = "\\s+");
    
    static std::string randomNumber(std::size_t length);
    
    
#ifdef _UNICODE
    static std::wstring utf82t(std::string_view utf8) {
            return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().from_bytes(utf8.data(), utf8.data() + utf8.size());
    }
    
    static  std::string t2utf8(std::wstring utf16) {
            return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(utf16.data(), utf16.data() + utf16.size());
    }
#else
    static std::string utf82t(const std::string& utf8) {
            return std::string(utf8);    // TODO implement
        }
    
    
    
    static std::string t2utf8(const std::string& utf8) {
        return utf8;
    }
    
    static std::string t2utf8(const std::wstring& utf8) {
        std::string str;
        std::transform(utf8.begin(), utf8.end(), std::back_inserter(str), [] (wchar_t c) {
            return (char)c;
        });
        return str;    // TODO implement
    }
#endif

#ifdef _UNICODE
        using t_sstream = std::wstringstream;
#define to_tstring(x) std::to_wstring(x)
#else
        using t_sstream = std::stringstream;
#define to_tstring(x) std::to_string(x)
#endif
    
};

} // namespace 

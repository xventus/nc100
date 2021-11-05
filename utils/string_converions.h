//
// vim: ts=4 et
// Copyright (c) 2015 AVAST Software a.s., www.avast.com
//

/// @file   iconv.h
/// @author Jan Schwarz (schwarzj@avast.com)
/// @since  2015-03-05


#pragma once

#include <stdint.h>
#include <string>
#include <stdexcept>
#include <iterator>


namespace fv::utils {

#ifdef _WIN32
    
#ifdef _UNICODE

    inline std::wstring& utf8_to_t(const std::string& utf, std::wstring& t) {
        t.clear();
        t.reserve(utf.size()); // most common case
        utf8_to_utf16(utf.begin(), utf.end(), std::back_inserter(t));
        return t;
    }
    inline std::wstring utf8_to_t(const std::string& utf) {
        std::wstring t;
        t.reserve(utf.size()); // most common case
        utf8_to_utf16(utf.begin(), utf.end(), std::back_inserter(t));
        return t;
    }
    inline std::wstring& utf8_to_t(const char* utf, std::wstring& t) {
        size_t utfLen = strlen(utf);
        t.clear();
        t.reserve(utfLen); // most common case
        utf8_to_utf16(utf, utf + utfLen, std::back_inserter(t));
        return t;
    }
    inline std::wstring utf8_to_t(const char* utf) {
        size_t utfLen = strlen(utf);
        std::wstring t;
        t.reserve(utfLen); // most common case
        utf8_to_utf16(utf, utf + utfLen, std::back_inserter(t));
        return t;
    }
    
    inline std::string& t_to_utf8(const std::wstring& t, std::string& utf) {
        utf.clear();
        utf.reserve(t.size()); // most common case
        utf16_to_utf8(t.begin(), t.end(), std::back_inserter(utf));
        return utf;
    }
    inline std::string t_to_utf8(const std::wstring& t) {
        std::string utf;
        utf.reserve(t.size()); // most common case
        utf16_to_utf8(t.begin(), t.end(), std::back_inserter(utf));
        return utf;
    }
    inline std::string& t_to_utf8(const wchar_t* t, std::string& utf) {
        size_t tLen = wcslen(t);
        utf.clear();
        utf.reserve(tLen); // most common case
        utf16_to_utf8(t, t + tLen, std::back_inserter(utf));
        return utf;
    }
    inline std::string t_to_utf8(const wchar_t* t) {
        size_t tLen = wcslen(t);
        std::string utf;
        utf.reserve(tLen); // most common case
        utf16_to_utf8(t, t + tLen, std::back_inserter(utf));
        return utf;
    }
    
#else

#error com::avast::utils::iconv ANSI version not implemented

#endif
    
#else
    
    // assume UTF-8 as default encoding
    
    inline std::string& utf8_to_t(const std::string& utf, std::string& t) {
        t = utf;
        return t;
    }
    inline std::string utf8_to_t(const std::string& utf) {
        return std::string(utf);
    }
    inline std::string& utf8_to_t(const char* utf, std::string& t) {
        t = utf;
        return t;
    }
    inline std::string utf8_to_t(const char* utf) {
        return std::string(utf);
    }
    
    inline std::string& t_to_utf8(const std::string& t, std::string& utf) {
        utf = t;
        return utf;
    }
    inline std::string t_to_utf8(const std::string& t) {
        return std::string(t);
    }
    inline std::string& t_to_utf8(const char* t, std::string& utf) {
        utf = t;
        return utf;
    }
    inline std::string t_to_utf8(const char* t) {
        return std::string(t);
    }
#endif


}

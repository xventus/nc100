//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   strurl.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30
/*
 
 std::string d("https://fotoventus.cz:443/file.ext?param=value&param2=value2");
 std::string d("fotoventus.cz:443/file.ext?param=value&param2=value2");
 std::string d("/file.ext?param=value&param2=value2");
 
 auto v = fv::utils::DomainParser::parse(d);
 std::cout << "Protocol:" << v.Protocol  << "\nHost:" << v.Host << "\nPort:" << v.Port << "\nPath:" << v.Path  << "\nQuery:" << v.QueryString << "\n";
 
 */

#pragma once

#include <string>
#include <string_view>
#include <algorithm>
#include <cctype>
#include <string>

namespace fv::utils {

    class DomainParser {
    private:
        std::string _queryString;
        std::string _path;
        std::string _protocol;
        std::string _host;
        std::string _port;
    public:
        
        void parse(const std::string& uri);
        
        std::string getQueryString() const {
            return _queryString;
        }
        
        std::string getPath() const {
            return _path;
        }

        std::string getProtocol() const {
            return _protocol;
        }

        std::string getHost() const {
            return _host;
        }

        std::string getPort() const {
            return _port;
        }

        
    private:
        
        unsigned char fromHex(unsigned char ch);
        
        const std::string urlDecode(const std::string& str);
    };


} // namespace


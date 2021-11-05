//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   strurl.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30

#include "strurl.h"

namespace fv::utils {


      
    void DomainParser::parse(const std::string& uri) {
        
        typedef std::string::const_iterator iter;

        do {
                if (uri.empty()) {
                    break;
                }
                   
                auto uriEnd = uri.end();

                // get query start
                auto queryStart = std::find(uri.begin(), uriEnd, '?');

                // protocol
                auto protocolStart = uri.begin();
                auto protocolEnd = std::find(protocolStart, uriEnd, ':');

                if (protocolEnd != uriEnd)
                {
                    std::string prot = &*(protocolEnd);
                    if ((prot.length() > 3) && (prot.substr(0, 3) == "://")) {
                        _protocol = std::string(protocolStart, protocolEnd);
                        protocolEnd += 3;
                    }
                    else {
                        protocolEnd = uri.begin();
                    }
                }
                else {
                    protocolEnd = uri.begin();
                }
            
                // host
                auto hostStart = protocolEnd;
                auto pathStart = std::find(hostStart, uriEnd, '/');

                auto hostEnd = std::find(protocolEnd,
                    (pathStart != uriEnd) ? pathStart : queryStart,
                    ':');  // check for port

                _host = std::string(hostStart, hostEnd);

                // port
                if ((hostEnd != uriEnd) && ((&*(hostEnd))[0] == ':'))  // we have a port
                {
                    hostEnd++;
                    auto portEnd = (pathStart != uriEnd) ? pathStart : queryStart;
                    _port = std::string(hostEnd, portEnd);
                }

                // path
                if (pathStart != uriEnd)
                    _path = std::string(pathStart, queryStart);

                // query
                if (queryStart != uriEnd)
                    _queryString = std::string(queryStart, uri.end());
            } while(false);
            }


        //------------------------------------------------------------------------------------------------------------------


        unsigned char DomainParser::fromHex(unsigned char ch) {
            if (ch <= '9' && ch >= '0')
                ch -= '0';
            else if (ch <= 'f' && ch >= 'a')
                ch -= 'a' - 10;
            else if (ch <= 'F' && ch >= 'A')
                ch -= 'A' - 10;
            else
                ch = 0;
            return ch;
        }

        //------------------------------------------------------------------------------------------------------------------
        //
        const std::string DomainParser::urlDecode(const std::string& str) {
            using namespace std;
            string result;
            string::size_type i;
            for (i = 0; i < str.size(); ++i)
            {
                if (str[i] == '+')
                {
                    result += ' ';
                }
                else if (str[i] == '%' && str.size() > i + 2)
                {
                    const unsigned char ch1 = fromHex(str[i + 1]);
                    const unsigned char ch2 = fromHex(str[i + 2]);
                    const unsigned char ch = (ch1 << 4) | ch2;
                    result += ch;
                    i += 2;
                }
                else
                {
                    result += str[i];
                }
            }
            return result;
        }

 



} // namespace

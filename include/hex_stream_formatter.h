
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   hex_stream_formatter.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-31

#pragma once


#include <memory>
#include <sstream>
#include <iostream>
#include <iomanip>


namespace fv::utils {
   
            /// Insert formated hexdump into output stream.
            template<class Tdata>
            class HexDumper {
            private:
                const Tdata& _data;
                size_t       _columns;
            public:
                HexDumper(const Tdata& data, size_t columns = 16) : _data(data), _columns(columns) {}

                friend std::ostream& operator<<(std::ostream& os, const HexDumper& tx) {
                    std::string line;
                    size_t pos, col, len;
                    char   ch;

                    if (tx._columns != 0) {

                        std::ios_base::fmtflags original_flags = os.flags();

                        len = tx._data.size();
                        pos = 0;
                        for (;;) {

                            os << std::hex << std::setw(6) << std::setfill(std::ostream::char_type('0')) << (pos / tx._columns * tx._columns) << ": ";
                            os.flags(original_flags);

                            // HEX view
                            col = 0;
                            while ((col < tx._columns) && ((pos + col) < len)) {
                                os << std::hex << std::setw(2) << std::setfill(std::ostream::char_type('0')) << (unsigned int)((unsigned char)tx._data.at(pos + col)) << " ";
                                col++;
                            }
                            os.flags(original_flags);
                            while (col < tx._columns) {
                                os << "   ";
                                col++;
                            }
                            os.flags(original_flags);

                            // ASCII view
                            os << "[ ";
                            col = 0;
                            while ((col < tx._columns) && ((pos + col) < len)) {
                                ch = tx._data.at(pos + col);
                                if ((ch < 32) || (ch >= 127))
                                    ch = '.';
                                os << ch;
                                col++;
                            }
                            os.flags(original_flags);
                            while (col < tx._columns) {
                                os << " ";
                                col++;
                            }
                            os.flags(original_flags);
                            os << " ]" << std::endl;


                            // move over line, break the loop if done
                            pos += tx._columns;
                            if (pos >= len)
                                break;
                        }

                        os.flags(original_flags);
                    }

                    return os;
                }
            };

        }
    

//------------------------------------------------------------------------------------------------------------------

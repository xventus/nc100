//
//  crc16.hpp
//  base
//
//  Created by Petr Vanek on 18.09.2021.
//

#pragma once
#include <stdint.h>
#include <string>

namespace fv {
class CRC {
public:
    
    
    static  int16_t crc16_ccitt_xmodem(const std::string_view& data);
};

}

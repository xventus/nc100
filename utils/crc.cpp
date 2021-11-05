//
//  crc16.cpp
//  base
//
//  Created by Petr Vanek on 18.09.2021.
//

#include "crc.h"
namespace fv {

/* CRC16 implementation acording to CCITT standards */
// CRC-CCITT    0x1021    x^{16} + x^{12} + x^5 + 1
// https://crccalc.com

int16_t CRC::crc16_ccitt_xmodem(const std::string_view &data)
{
  int16_t crc;
  uint8_t n;
  crc = 0;
 auto index = data.length();
  while (index > 0 ) {
    crc = crc ^ (int8_t)data[data.length() - index] << 8;
    index --;
    n = 8;
    do {
      if (crc & 0x8000)
        crc = crc << 1 ^ 0x1021;
      else
        crc = crc << 1;
    } while (--n);
  }
  return crc;
}

} // namespace fv

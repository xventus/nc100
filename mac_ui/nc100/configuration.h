//
//  configuration.h
//  nc100
//
//  Created by Petr Vanek on 05.10.2021.
//

#ifndef configuration_hpp
#define configuration_hpp

#include <stdio.h>
#include <QSettings>
#include <QString>

// core
#include "../../include/crosstypes.h"
#include "../../include/serial_enumerator_intf.h"
#include "../../include/hex_stream_formatter.h"
#include "../../include/modem.h"

class Configuration
{
public:
    ///> serial configuration
    struct Cfg{
        fv::serial::BDSpeed     _speedS {fv::serial::BDSpeed::bd9600} ;
        fv::serial::DataBits    _bitsS {fv::serial::DataBits::b8} ;
        fv::serial::FlowControl _flowS {fv::serial::FlowControl::none};
        fv::serial::Parity      _parityS {fv::serial::Parity::none};
        fv::serial::StopBits    _stopsS {fv::serial::StopBits::stop_1};
        bool                    _toFile {false};
        bool                    _autoincrement {false};
        int                     _filter {0};
        int                     _protocol {0};
        t_tstr                  _base;
        t_tstr                  _recName;
    };
   /*
    Configuration(const t_tstr& filepath) :  _filePath(filepath) {
    };
*/
     static  void read(Cfg &cfg);
     static  void write(const Cfg &cfg);
    
    
};
    

#endif /* configuration_hpp */

//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   serial.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30

#pragma once

#include <string>
#include <sstream>
#include <vector>
#include "../include/serial_enumerator_intf.h"
#include "serial.h"

namespace fv::serial {


class SerialEnumerator : public ISerialEnumerator {
    private:
       
    
    public:
        virtual ~SerialEnumerator() = default;
        virtual t_vector_serial scan()  override;
        
    
    private:
    
};

   
} // namespace 

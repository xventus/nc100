//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   serial_enumerator_intf.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30

#pragma once

#include <stdexcept>
#include "serial_intf.h"

namespace fv::serial {

using t_vector_serial = std::vector<std::unique_ptr<ISerial>>;

class ISerialEnumerator {
    public:

        virtual ~ISerialEnumerator() = default;
        
        virtual t_vector_serial scan() = 0;
    
    struct Factory {
      static std::unique_ptr<ISerialEnumerator> createUnique();
    };
    
};
   
}

//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   mac_misc.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30

#pragma once

#include <string>
#include <variant>
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/serial/IOSerialKeys.h>
#include <IOKit/IOBSD.h>

namespace fv::utils {

class MACClasses {
    
    public: 
    
    using proNumber = std::variant<std::monostate, uint8_t, uint16_t, uint32_t, uint64_t>;

    static std::string  getObjectPropertyString(io_object_t& mport, const std::string_view& propertyName);
    static proNumber getObjectPropertyNumber(io_object_t& mport, const std::string_view& propertyName, CFNumberType numtype);
    static std::string CFStr2StdStr(CFStringRef str);
    static std::string getClassName(io_object_t& id);
    static std::string getDeviceLocation( io_object_t& id );
    static io_registry_entry_t getParentEntry( io_object_t& serial_port, const std::string_view &className);
};

}

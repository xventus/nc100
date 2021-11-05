//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   serial.cpp
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30

#include "mac_enumerator.h"
#include  "strop.h"
#include "../include/exceptions.h"
#include "../utils/mac_misc.h"

namespace fv::serial {

std::unique_ptr<ISerialEnumerator> ISerialEnumerator::Factory::createUnique() {
         return std::make_unique<SerialEnumerator>();
}


t_vector_serial SerialEnumerator::scan() {
     
    //std::unique_ptr<ISerial> dd;
    //vec.push_back(std::move(ptr2x));
    t_vector_serial rc;
    
    io_object_t scanned;
    mach_port_t machPort;
    io_iterator_t ioter;
    
    // Returns the mach port used to initiate communication with IOKit.
    auto krc = IOMasterPort(MACH_PORT_NULL, &machPort);

    if(krc != KERN_SUCCESS) {
        throw exceptions::core_error("IOMasterPort failed");
    }
      
    // Create a matching dictionary that specifies an IOService class match.
    auto matchedClasses = IOServiceMatching(kIOSerialBSDServiceValue);

    if (matchedClasses == nullptr) {
        throw exceptions::core_error("IOServiceMatching failed");
    }

    CFDictionarySetValue( matchedClasses, CFSTR(kIOSerialBSDTypeKey), CFSTR(kIOSerialBSDAllTypes));
    krc = IOServiceGetMatchingServices(machPort, matchedClasses, &ioter);
    if (krc != KERN_SUCCESS) {
        throw exceptions::core_error("IOServiceGetMatchingServices failed");
    }
    
    while ((scanned = IOIteratorNext(ioter))) {

        std::string location = fv::utils::MACClasses::getDeviceLocation( scanned );
        io_registry_entry_t parent = fv::utils::MACClasses::getParentEntry( scanned, "IOUSBDevice" );
        IOObjectRelease(scanned);

        if( location.empty() ) {
            continue;
        }
        
        auto port = ISerial::Factory::createUnique();
        port->withVendorName(fv::utils::StrOp::trim(fv::utils::MACClasses::getObjectPropertyString(parent, "USB Vendor Name")))
        .withDeviceName(fv::utils::StrOp::trim( fv::utils::MACClasses::getObjectPropertyString(parent, "USB Product Name")))
        .withDeviceLocation(location);
             
        auto sn = fv::utils::MACClasses::getObjectPropertyString( parent, "USB Serial Number" );
        auto  product = fv::utils::MACClasses::getObjectPropertyNumber( parent, "idProduct", kCFNumberSInt16Type );
        auto  vendor = fv::utils::MACClasses::getObjectPropertyNumber( parent, "idVendor", kCFNumberSInt16Type);
        if (std::holds_alternative<uint16_t>(vendor) && std::holds_alternative<uint16_t>(product)) {
            port->withHWinfo(std::get<uint16_t>(vendor), std::get<uint16_t>(product));
        }
               
        rc.emplace_back(std::move(port));
        
    }

    IOObjectRelease(ioter);
   
    return rc;
    
}
        

} // namespace

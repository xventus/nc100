//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   mac_misc.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30


#include "mac_misc.h"

namespace fv::utils {


std::string MACClasses::getClassName(io_object_t& id) {
    std::string rc;
    io_name_t name;
  
    if( IOObjectGetClass( id, name ) == KERN_SUCCESS ) {
        rc = name;
    }

    return rc;
}



std::string MACClasses::CFStr2StdStr(CFStringRef str ) {
    std::string rc;
    char tmp[512];
    if(str) {
        if (CFStringGetCString(str,tmp, sizeof(tmp), kCFStringEncodingASCII)) {
            rc = tmp;
        } else {
            rc.clear();
        }
    }

    return rc;
}


std::string  MACClasses::getObjectPropertyString(io_object_t& mport, const std::string_view& propertyName) {
    std::string rc;

    if(mport) {
        CFStringRef propName = CFStringCreateWithCString (kCFAllocatorDefault, std::string(propertyName).c_str(), kCFStringEncodingASCII);
        CFTypeRef nameStr = IORegistryEntryCreateCFProperty( mport, propName, kCFAllocatorDefault, 0);
        if( nameStr ) {
            if(CFGetTypeID(nameStr) == CFStringGetTypeID()) {
                rc = CFStr2StdStr(static_cast<CFStringRef>(nameStr));
            }
            
            CFRelease(nameStr);
        }

        if(propName) {
            CFRelease(propName);
        }
    }

    return rc;
}


MACClasses::proNumber MACClasses::getObjectPropertyNumber(io_object_t& mport, const std::string_view& propertyName, CFNumberType numtype) {
    proNumber rc = std::monostate{};
        if( mport ) {
        auto propStr = CFStringCreateWithCString(kCFAllocatorDefault, std::string(propertyName).c_str(), kCFStringEncodingASCII);
        auto number = IORegistryEntryCreateCFProperty(mport, propStr, kCFAllocatorDefault, 0);
        if(propStr) {
            CFRelease(propStr);
        }
        
        if(number) {
            if(CFGetTypeID(number) == CFNumberGetTypeID()) {
                if (numtype == kCFNumberSInt16Type) {
                    uint16_t rc16_t = 0;
                    if (CFNumberGetValue(static_cast<CFNumberRef>(number), numtype, &rc16_t)) {
                    rc = rc16_t;
                    }
                } else if (numtype == kCFNumberSInt32Type) {
                    uint32_t rc32_t = 0;
                    if (CFNumberGetValue(static_cast<CFNumberRef>(number), numtype, &rc32_t)) {
                    rc = rc32_t;
                    }
                } else if (numtype == kCFNumberSInt64Type) {
                    uint64_t rc64_t = 0;
                    if (CFNumberGetValue(static_cast<CFNumberRef>(number), numtype, &rc64_t)) {
                    rc = rc64_t;
                    }
                } else if (numtype == kCFNumberSInt8Type) {
                    uint8_t rc8_t = 0;
                    if (CFNumberGetValue(static_cast<CFNumberRef>(number), numtype, &rc8_t)) {
                    rc = rc8_t;
                    }
                }
            }
            
        }
        
        CFRelease(number);
    }
    
    return rc;
    }


std::string MACClasses::getDeviceLocation( io_object_t& id ) {
    std::string location;
    CFTypeRef reflocation;

    reflocation = IORegistryEntryCreateCFProperty( id, CFSTR(kIOCalloutDeviceKey), kCFAllocatorDefault, 0);
    if (reflocation) {
        if( CFGetTypeID(reflocation) == CFStringGetTypeID()){
            location = fv::utils::MACClasses::CFStr2StdStr(static_cast<CFStringRef>(reflocation));
        }

        CFRelease(reflocation);
    }

    return location;
}



io_registry_entry_t MACClasses::getParentEntry( io_object_t& serial_port, const std::string_view &className ) {

    io_registry_entry_t rc = 0;
    
    io_object_t device = serial_port;
    io_registry_entry_t parent = 0;

    kern_return_t kern_result = KERN_FAILURE;
    std::string name = fv::utils::MACClasses::getClassName(device);

    while( name.compare(className) != 0  ) {
        kern_result = IORegistryEntryGetParentEntry(device, kIOServicePlane, &parent);

        if(kern_result != KERN_SUCCESS) {
            rc = 0;
            break;
        }

        device = parent;
        name = fv::utils::MACClasses::getClassName(device);
    }

    if(kern_result == KERN_SUCCESS) {
        rc = device;
    }

    return rc;
}


}

//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   timeop.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30

#pragma once

#include <cstdio>
#include <cinttypes>
#include <string>
#include <sstream>
#include <time.h>
/*
#ifdef __MACH__
#include <mach/mach_time.h>
#endif
*/

namespace fv::utils {


class  TimeOp {
  
public:
    
    static timespec msToTimeSpec(uint64_t ms);
   
    
};


} // namespace 




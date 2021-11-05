//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   tmop.cpp
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30

#include  "tmop.h"

namespace fv::utils {


    timespec TimeOp::msToTimeSpec(uint64_t ms) {
        timespec rc;
        rc.tv_sec = ms / 1000;
        rc.tv_nsec = (ms - (rc.tv_sec * 1000)) * 1000000;
        return rc;
    }


} // namespace  

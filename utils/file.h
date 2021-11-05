//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   file.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30

#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include "../include/crosstypes.h"

namespace fv::utils {

class  SimpleFileOp {
public:
  
    template <class Type>
    static void write(t_tstr file, const Type& obj) {
        std::ofstream stream(file.c_str(), std::ios::out | std::ios::binary);
        stream.write(obj.data(),obj.size());
        stream.close();
    }

    template <class Type>
    static void read(t_tstr file, Type& obj) {
        std::ifstream stream (file.c_str(), std::ios::in | std::ios::binary);
        if (stream.is_open()) {
            obj.assign((std::istreambuf_iterator<char>(stream)), (std::istreambuf_iterator<char>()));
        stream.close();
    }

    
        
    }

};

}

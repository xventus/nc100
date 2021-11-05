//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   command_hint_intf.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-09-09


#pragma once

#include "crosstypes.h"
#include <string_view>

namespace fv::ui {

    class ICommandHint {
    public:

        virtual t_tstr getHint(std::string_view menuName) const = 0;

    };

}

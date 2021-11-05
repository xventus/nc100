//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   command_lib_intf.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-09-09


#pragma once

#include <functional>

namespace fv::ui {

    class ICommandLib {
    public:

        virtual void enumCommands(std::function< void(std::string_view name, const TCHAR* help) > fn) const = 0;

        virtual bool searchCommand(std::string_view name, std::function< void(std::string_view name, const TCHAR* help) > fn) const = 0;

    };

} 

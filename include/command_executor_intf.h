//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   command_executor_intf.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-31

#pragma once


#include "exceptions.h"

namespace fv::ui {

    class ICommandExecutor {
    public:
        virtual void executeCommand(std::string_view name) = 0;

    };

} // namespace asw::bgvault::cli

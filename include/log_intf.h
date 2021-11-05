//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   log_intf.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30


#pragma once

#include <cstdarg>
#include <memory>
#include "crosstypes.h"

namespace fv {
    
    struct ILogger {
    public:

        /// Severity of the event.
        enum class EventSeverity {
              _unspecified = -1    ///< unspecified severity (don't use for message severity)
             , debug = 0           ///< debug logging
             , info = 1            ///< informational logging
             , error = 2           ///< error logging
        };


        virtual ~ILogger() = default;

        virtual bool isExclusive() const = 0;

        virtual void logEvent(EventSeverity severity, const TCHAR* fmt, va_list args) = 0;

    };

    class ILogComponent {
    public:

        virtual void setLogSeverity(ILogger::EventSeverity severity) = 0;

        virtual void setLogger(std::shared_ptr<ILogger> logger) = 0;

    };
    
}


//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   logger.cpp
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30

#include "logger.h"

#include <cstdarg>
#include <cassert>

namespace fv::detail  {

    // ---

    std::unique_ptr<LogComponent> LogComponent::_instance;
    std::once_flag LogComponent::_onceFlag;
    // ---

LogComponent::LogComponent() {
        _severity_level = ILogger::EventSeverity::_unspecified;
    }

LogComponent* LogComponent::getInstance() {
        std::call_once(_onceFlag, [] {
            _instance.reset(new LogComponent);
        });
        return _instance.get();
    }

    void LogComponent::setLogSeverity(ILogger::EventSeverity severity) {
        _severity_level = severity;
    }

    void LogComponent::setLogger(std::shared_ptr<ILogger> logger) {
        std::atomic_store(&_logger, logger);
    }

    bool LogComponent::isSeverityImportatnt(ILogger::EventSeverity severity) {
        return severity >= _severity_level;
    }

    void LogComponent::event(ILogger::EventSeverity severity, const TCHAR* fmt, ...) {

        assert(fmt != nullptr);

        try {

            if (isSeverityImportatnt(severity)) {

                va_list arglist;
                va_start(arglist, fmt);

                auto logger = std::atomic_load(&_logger);
                if (logger) {

                    // use custom logger
                    logger->logEvent(severity, fmt, arglist);

                }

                va_end(arglist);
            }
        } catch (...) {
            // try to not break the app due to logger mishaps
        }
    }

} 

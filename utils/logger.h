//
// vim: ts=4
// Copyright (c) 2021 Petr Vanek,www.fotoventus.cz
//

/// @file   logger.h
/// @author Petr Vanek (petr@fotoventus.cz)
/// @since  2021-08-30

#pragma once

#include "../include/log_intf.h"
#include <atomic>
#include <mutex>

namespace fv::detail {
    
    /// logger implementation.
    class LogComponent : public ILogComponent {
    private:

       
        static std::unique_ptr<LogComponent> _instance;         ///> singleton instance
        static std::once_flag _onceFlag;                        ///>    singlton initialization flag
        std::atomic<ILogger::EventSeverity> _severity_level;    ///> minimum event level that will be logged
        std::shared_ptr<ILogger> _logger;                        /// alternative logger

    public:

        LogComponent();
        
        virtual ~LogComponent() = default;

        /// Returns component instance.
        /// @return Component instance.
        static LogComponent* getInstance();

        /// Writes the event to the log.
        /// @param severity Severity level associated with the event. The event may be ignored if the severity of the event is not important.
        /// @param fmt Format control string. See printf documentation for available formatting options.
        /// @param ... Optional arguments of the format control string.
        void event(ILogger::EventSeverity severity, const TCHAR* fmt, ...);

        /// Sets the minimum severity of an event that shall be written to the log.
        /// Depending on actual platform, it may perform additional operations (_WIN32 & asw::log).
        /// @param severity All events below this severity will be ignored.
        virtual void setLogSeverity(ILogger::EventSeverity severity) override;

        virtual void setLogger(std::shared_ptr<ILogger> logger) override;

    private:

        LogComponent(const LogComponent&) = delete;

        LogComponent& operator=(const LogComponent&) = delete;

        /// Tests the importance of the severity of the event.
        /// @param severity Severity of the event.
        /// @return true if the event should be logged or false otherwise.
        bool isSeverityImportatnt(ILogger::EventSeverity severity);

    };

}


// Log event with specific severity level.
#define log_message_debug(...)   fv::detail::LogComponent::getInstance()->event(ILogger::EventSeverity::debug, __VA_ARGS__);
#define log_message_info(...)    fv::detail::LogComponent::getInstance()->event(ILogger::EventSeverity::info,  __VA_ARGS__);
#define log_message_error(...)   fv::detail::LogComponent::getInstance()->event(ILogger::EventSeverity::error, __VA_ARGS__);

#ifdef _UNICODE
#define log_fn_message_debug(...)   fv::detail::LogComponent::getInstance()->event(ILogger::EventSeverity::debug, __FUNCTIONW__ L" - " __VA_ARGS__);
#define log_fn_message_info(...)    fv::detail::LogComponent::getInstance()->event(ILogger::EventSeverity::info,  __FUNCTIONW__ L" - " __VA_ARGS__);
#define log_fn_message_error(...)   fv::detail::LogComponent::getInstance()->event(ILogger::EventSeverity::error, __FUNCTIONW__ L" - " __VA_ARGS__);
#else
#define log_fn_message_debug(...)   fv::detail::LogComponent::getInstance()->event(ILogger::EventSeverity::debug, __FUNCTION__ " - " __VA_ARGS__);
#define log_fn_message_info(...)    fv::detail::LogComponent::getInstance()->event(ILogger::EventSeverity::info,  __FUNCTION__ " - " __VA_ARGS__);
#define log_fn_message_error(...)   fv::detail::LogComponent::getInstance()->event(ILogger::EventSeverity::error, __FUNCTION__ " - " __VA_ARGS__);
#endif

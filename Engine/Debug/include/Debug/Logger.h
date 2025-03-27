//
// Created by Lama on 01/02/2025.
//
#pragma once

#include <cstdarg>
#include <cstdio>
#include <filesystem>
#include <functional>
#include <vector>
#include <fmt/core.h>

#include "Debug/Preprocessor.h"

// Duplicated from CoreInterfaces to prevent dependency on this module
#if ML_REDEFINE_HANDLE
template <typename T>
using Handle = std::shared_ptr<T>;

template <typename T, typename... Args>
Handle<T> MakeHandle(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}
#else
#include "CoreInterfaces/Types.h"
#endif
//

namespace MLEngine
{
    class LogHandlerInterface;

    enum class LogLevel : std::uint8_t
    {
        Invalid,
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Critical,
    };

    struct LogEvent
    {
        std::string message;
        std::uint64_t time;
        void* userData;
        LogLevel level;
        std::string FileLocation;
    };

    class Logger
    {
    public:
        Logger() = delete;

        static void SetLevel(const LogLevel new_level) { level = new_level; }

        static void AddHandler(Handle<LogHandlerInterface> logHandler);

        static void Log(const LogLevel&& level, const std::string&& message, const std::string&& file_name,
                        const uint32_t&& line);

        static const std::string& GetLogLevelString(LogLevel level);
        static std::string GetDefaultFormattedMessage(const LogEvent& event);

    private:
        static std::vector<Handle<LogHandlerInterface>> logHandlers;
        static LogLevel level;
    };
}

// LOGGING
#define ML_FMT(formatString, ...) fmt::format(formatString ML_EXPAND_ARGS(__VA_ARGS__))
#define INTERNAL_ML_LOG(level, fmt, ...) ::MLEngine::Logger::Log(::MLEngine::LogLevel::level, ML_FMT(fmt, __VA_ARGS__), __FILE__, __LINE__)

#ifdef ML_DEBUG

#define MLLogTrace(fmt, ...) INTERNAL_ML_LOG(Trace, fmt, __VA_ARGS__)
#define MLLogDebug(fmt, ...) INTERNAL_ML_LOG(Debug, fmt, __VA_ARGS__)
#define MLLogInfo(fmt, ...) INTERNAL_ML_LOG(Info, fmt, __VA_ARGS__)
#define MLLogWarn(fmt, ...) INTERNAL_ML_LOG(Warning, fmt, __VA_ARGS__)
#define MLLogError(fmt, ...) INTERNAL_ML_LOG(Error, fmt, __VA_ARGS__)
#define MLLogFatal(fmt, ...) INTERNAL_ML_LOG(Critical, fmt, __VA_ARGS__)

#else

#define MLLogTrace(...)
#define MLLogDebug(...)
#define MLLogInfo(...)
#define MLLogWarn(...)
#define MLLogError(...)
#define MLLogFatal(...)

#endif

//
// Created by Lama on 01/02/2025.
//
#pragma once

#include <cstdio>
#include <vector>
#include <cstdarg>

#include <filesystem>
#include <functional>

#include "CoreInterfaces/ModuleInterface.h"
#include "CoreInterfaces/Types.h"


namespace MLEngine
{
    enum class LogLevel : UInt16
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
        UInt64 time;
        void* userData;
        LogLevel level;
        std::string FileLocation;
    };
    using LogFn = std::function<void(const LogEvent*)>;

    namespace Internal
    {
        const char* GetLogLevelString(LogLevel level);
    }


    void StdOutLogCallback(const LogEvent* ev);

    std::string GetDefaultFormattedLogMessage(const LogEvent* ev);
}

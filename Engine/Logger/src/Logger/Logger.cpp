//
// Created by Lama on 01/02/2025.
//

#include "Logger/Logger.h"

#include <iostream>

#include "CoreInterfaces/ModuleLocator.h"
#include "fmt/color.h"
#include "Logger/Module.h"


namespace MLEngine::Internal
{
    static constexpr const char* priorities_to_string[] = {
        "Invalid",
        "Trace",
        "Debug",
        "Info",
        "Warning",
        "Error",
        "Critical",
    };

    const char* GetLogLevelString(LogLevel level)
    {
        return priorities_to_string[static_cast<UInt16>(level)];
    }

    fmt::color GetLogLevelColor(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::Invalid:
            return fmt::color::red;
        case LogLevel::Trace:
            return fmt::color::white;
        case LogLevel::Debug:
            return fmt::color::yellow;
        case LogLevel::Info:
            return fmt::color::light_green;
        case LogLevel::Warning:
            return fmt::color::orange;
        case LogLevel::Error:
            return fmt::color::red;
        case LogLevel::Critical:
            return fmt::color::dark_red;
        default:
            return fmt::color::magenta;
        }
    }
}

void MLEngine::StdOutLogCallback(const LogEvent* ev)
{
    fmt::print(fmt::fg(Internal::GetLogLevelColor(ev->level)), "[{}][{}]:{}\n", Internal::GetLogLevelString(ev->level), ev->time, ev->message);
}

std::string MLEngine::GetDefaultFormattedLogMessage(const LogEvent* ev)
{
    return fmt::format("[{}][{}]:{}\n", Internal::GetLogLevelString(ev->level), ev->time, ev->message);
}

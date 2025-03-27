//
// Created by lama on 27/03/25.
//
#include "Debug/LogHandlers/ConsoleLogHandler.h"
#include "fmt/color.h"

namespace MLEngine
{
    // Assumes terminal background color is dark
    fmt::color GetLogLevelColor(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::Invalid:
            return fmt::color::red;
        case LogLevel::Trace:
            return fmt::color::dark_gray;
        case LogLevel::Debug:
            return fmt::color::yellow;
        case LogLevel::Info:
            return fmt::color::green;
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

    void ConsoleLogHandler::Log(const LogEvent& event)
    {
        fmt::print(
            fmt::fg(GetLogLevelColor(event.level)),
            "[{}][{}]:{}\n",
            Logger::GetLogLevelString(event.level), event.time, event.message
        );
    }
}

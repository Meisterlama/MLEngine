//
// Created by Lama on 01/02/2025.
//

#include "Debug/Logger.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <fmt/color.h>
#include <SDL3/SDL.h>

#include "Debug/LogHandlers/LogHandlerInterface.h"

namespace MLEngine::Internal
{
    static constexpr std::string priorities_to_string[] = {
        {"Invalid"},
        "Trace",
        "Debug",
        "Info",
        "Warning",
        "Error",
        "Critical",
    };

    const std::string& GetLogLevelString(LogLevel level)
    {
        return priorities_to_string[static_cast<uint16_t>(level)];
    }
}

namespace MLEngine
{
    std::vector<Handle<LogHandlerInterface>> Logger::logHandlers{};
    void Logger::AddHandler(Handle<LogHandlerInterface> logHandler)
    {
        logHandlers.push_back(logHandler);
    }

    const std::string& Logger::GetLogLevelString(LogLevel level)
    {
        return Internal::GetLogLevelString(level);
    }

    std::string Logger::GetDefaultFormattedMessage(const LogEvent& event)
    {
        return fmt::format(
                "[{}][{}]:{}\n",
                Internal::GetLogLevelString(event.level), event.time, event.message
            );
    }

    void Logger::Log(const LogLevel&& level, const std::string&& message, const std::string&& file_name,
                     const uint32_t&& line)
    {
        LogEvent event;
        event.level = level;
        event.message = message;
        event.FileLocation = fmt::format("[{}:{}]", file_name, line);
        event.time = SDL_GetTicks();

        for (const auto & logHandler : logHandlers)
        {
            logHandler->Log(event);
        }
    }
}

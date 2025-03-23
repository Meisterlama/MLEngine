//
// Created by lama on 22/03/25.
//

#include "Logger/Module.h"

#include <algorithm>

#include "Logger/Logger.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <fstream>

namespace MLEngine
{
    void LoggerModule::AddCallback(LogFn callback)
    {
        logCallbacks.push_back(callback);
    }

    void LoggerModule::AddFile(std::string FilePath)
    {
        Handle<std::ofstream> FileHandle = MakeHandle<std::ofstream>(
            FilePath, std::ios::app | std::ios::ate);
        if (FileHandle->is_open())
        {
            MLLogInfo("Logging initialized at: {}", FilePath);
        }
        else
        {
            MLLogError("Failed to open file: {}", FilePath);
        }
        AddCallback([FileHandle](const LogEvent* ev)
        {
            *FileHandle << GetDefaultFormattedLogMessage(ev);
        });
    }

    void LoggerModule::RemoveCallback(LogFn callback)
    {
        auto it = std::find_if(logCallbacks.begin(), logCallbacks.end(), [&callback](const LogFn& cb)
        {
            return cb.target_type() == callback.target_type();
        });

        if (it != logCallbacks.end())
        {
            logCallbacks.erase(it);
        }
    }


    void LoggerModule::ManualLog(const LogLevel level, const std::string&& message, const std::string&& file_name, const int&& line) const
    {
        LogEvent event;
        event.level = level;
        event.message = message;
        event.FileLocation = fmt::format("[FILE:{}:{}]", file_name, line);
        event.time = SDL_GetTicks();

        for (const auto & logCallback : logCallbacks)
        {
            logCallback(&event);
        }
    }
}

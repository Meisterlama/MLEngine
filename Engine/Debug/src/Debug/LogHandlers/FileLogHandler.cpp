//
// Created by lama on 27/03/25.
//
#include "Debug/LogHandlers/FileLogHandler.h"

#include <fstream>


MLEngine::FileLogHandler::FileLogHandler(const std::string& filePath)
{
    openedFileHandle = MakeHandle<std::ofstream>(
    filePath, std::ios::app | std::ios::ate);
    if (openedFileHandle->is_open())
    {
        MLLogInfo("Logging initialized at: {}", filePath);
    }
    else
    {
        MLLogError("Failed to open file: {}", filePath);
    }
}

void MLEngine::FileLogHandler::Log(const LogEvent& event)
{
    *openedFileHandle << event.message;
}

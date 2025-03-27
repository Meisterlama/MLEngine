//
// Created by lama on 27/03/25.
//
#pragma once
#include "LogHandlerInterface.h"

namespace MLEngine
{
    class FileLogHandler : public LogHandlerInterface
    {
    public:
        FileLogHandler(const std::string& filePath);
        ~FileLogHandler() override = default;

    private:
        void Log(const LogEvent& event) override;

        Handle<std::ofstream> openedFileHandle;
    };
}

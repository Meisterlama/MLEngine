//
// Created by lama on 27/03/25.
//
#pragma once
#include "Debug/LogHandlers/LogHandlerInterface.h"

namespace MLEngine
{
    class ConsoleLogHandler : public LogHandlerInterface
    {
        public:
            ConsoleLogHandler() = default;
            ~ConsoleLogHandler() override = default;

        private:
            void Log(const LogEvent& event) override;
    };
}

//
// Created by lama on 27/03/25.
//
#pragma once
#include "../Logger.h"

namespace MLEngine {
    class LogHandlerInterface
    {
    public:
        virtual ~LogHandlerInterface() = default;

    private:
        friend class Logger;

        virtual void Log(const LogEvent& event) = 0;
    };
}

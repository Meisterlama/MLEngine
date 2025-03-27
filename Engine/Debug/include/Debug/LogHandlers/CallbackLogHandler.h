//
// Created by lama on 27/03/25.
//
#pragma once
#include <utility>

#include "Debug/LogHandlers/LogHandlerInterface.h"

namespace MLEngine
{
    class CallbackLogHandler : public LogHandlerInterface {
    public:
        CallbackLogHandler(std::function<void(const LogEvent&)> callback) : callback(std::move(callback)) {};
        ~CallbackLogHandler() override = default;

    private:
        void Log(const LogEvent& event) override;
        std::function<void(const LogEvent&)> callback;
    };
}

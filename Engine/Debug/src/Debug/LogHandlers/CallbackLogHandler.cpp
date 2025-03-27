//
// Created by lama on 27/03/25.
//
#include "Debug/LogHandlers/CallbackLogHandler.h"

namespace MLEngine {
    void CallbackLogHandler::Log(const LogEvent& event)
    {
        callback(event);
    }
}

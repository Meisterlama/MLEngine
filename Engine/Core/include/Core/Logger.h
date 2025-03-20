//
// Created by Lama on 01/02/2025.
//
#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <SDL3/SDL_log.h>

namespace MLEngine {
    class Logger {
    public:
        Logger();

        ~Logger();

        void ShowLogWindow();

    private:
        struct LogEvent {
            std::string message;
            int priority;
        };

        static void LogOutputFunction(void *userdata, int category, SDL_LogPriority priority, const char *message);

        std::unordered_map<int, std::vector<LogEvent> > logs;
    };
}

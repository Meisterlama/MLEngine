//
// Created by Lama on 01/02/2025.
//

#include "../../include/Core/Logger.h"

#include "imgui.h"
#include "Core/Engine.h"

namespace MLEngine
{
    namespace Internal
    {
        static const char* categories_to_string[] = {
            "APPLICATION",
            "ERROR",
            "ASSERT",
            "SYSTEM",
            "AUDIO",
            "VIDEO",
            "RENDER",
            "INPUT",
            "TEST",
            "GPU",
        };

        static const char* priorities_to_string[] = {
            "INVALID",
            "TRACE",
            "VERBOSE",
            "DEBUG",
            "INFO",
            "WARN",
            "ERROR",
            "CRITICAL",
            "COUNT"
        };
    }


    Logger::Logger()
    {
        SDL_SetLogOutputFunction(LogOutputFunction, this);
    }

    Logger::~Logger()
    {
        SDL_SetLogOutputFunction(SDL_GetDefaultLogOutputFunction(), nullptr);
    }

    void Logger::ShowLogWindow()
    {
        ImGui::Begin("Logger");
        for (const auto& [category, log_events] : logs)
        {
            if (ImGui::CollapsingHeader(Internal::categories_to_string[category]))
            {
                for (const auto& event : log_events)
                {
                    ImGui::TextWrapped("[%s] %s",
                                Internal::priorities_to_string[event.priority],
                                event.message.c_str()
                    );
                }
            }
        }
        ImGui::End();
    }

    void Logger::LogOutputFunction(void* userdata, int category, SDL_LogPriority priority, const char* message)
    {
        SDL_GetDefaultLogOutputFunction()(userdata, category, priority, message);
        Logger* logger = static_cast<Logger*>(userdata);
        logger->logs[category].emplace_back(LogEvent{std::string(message), priority});
        if (gEngine)
        {
            gEngine->console.Log(std::string(message));
        }
    }
}

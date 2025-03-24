//
// Created by Lama on 01/02/2025.
//
#pragma once

#include <memory>
#include <string>
#include <utility>

#include "Console.h"
#include "CoreInterfaces/Types.h"
#include "Platform/PlatformEvent.h"


namespace MLEngine
{
    class Window;
    class ApplicationInterface;

    class Engine;
    extern Engine* s_engine;

    class Engine
    {
    public:
        Engine() = default;

        ~Engine() = default;

        void RegisterInputEventCallbacks();

        void Init(Handle<ApplicationInterface> application);

        void Update();

        void ProcessEvent(const PlatformEvent* event);

        void Shutdown();

        bool ShouldQuit();

        void RequestShutdown(std::string reason = "Unknown")
        {
            shutdownReason = std::move(reason);
            shutdownRequested = true;
        };

        bool isPlaying = false;

    public:
        Handle<Window> defaultWindow = nullptr;
        Console console;

        Handle<ApplicationInterface> currentApplication = nullptr;

        uint64_t lastTick = 0;
        bool freezeTime = false;

        bool shutdownRequested = false;
        std::string shutdownReason{};
    };
}

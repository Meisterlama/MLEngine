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
    class GraphicsContext;
    class Window;
    class Renderer;
}

namespace MLEngine
{
    class ApplicationInterface;
}

namespace MLEngine
{
    class Engine;
    extern Engine* s_engine;

    class Engine
    {
    public:
        Engine() = default;

        ~Engine() = default;

        void RegisterInputEventCallbacks();

        void Init(ApplicationInterface* application);

        void Update();

        void ProcessEvent(const PlatformEvent* event);

        void Shutdown();

        bool ShouldQuit();

        void RequestShutdown(std::string reason = "Unknown")
        {
            ShutdownReason = std::move(reason);
            bShutdownRequested = true;
        };

        bool isPlaying = false;

    public:
        Handle<Window> default_window = nullptr;
        Handle<GraphicsContext> default_gcontext = nullptr;
        Console console;

        ApplicationInterface* current_application = nullptr;

        uint64_t last_tick = 0;
        bool freeze_time = false;

        bool bShutdownRequested = false;
        std::string ShutdownReason{};
    };
}

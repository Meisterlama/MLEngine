//
// Created by Lama on 01/02/2025.
//
#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <CoreInterfaces/Types.h>
#include <SDL3/SDL_events.h>
#include "Core/CreateCube.h"

#include "Console.h"

#ifdef ML_RENDERING
    #define ML_GLSL_VERSION "#version 130"
#endif

namespace MLEngine
{
    class Renderer;
}

namespace MLEngine
{
    class ApplicationInterface;
}

namespace MLEngine {
    class Engine;
    class ResourceManager;
    class GraphicsContext;
    class Window;
    class Logger;
    class Mesh;
    class Shader;
    class Camera;

    extern Engine *gEngine;

    class Engine {
    public:
        Engine();

        ~Engine();

        void RegisterInputEventCallbacks();

        void Init(ApplicationInterface* application);

        void Update();

        void ProcessEvent(SDL_Event *event);

        void Shutdown();

        bool ShouldQuit();

        inline void RequestShutdown(std::string reason = "Unknown") {
            ShutdownReason = std::move(reason);
            bShutdownRequested = true;
        };

        bool isPlaying = false;

    public:
        Handle<Logger> default_logger = nullptr;
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

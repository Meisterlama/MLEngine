//
// Created by Lama on 01/02/2025.
//
#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <SDL3/SDL_events.h>

#include "Console.h"
#include "Rendering/Camera.h"
#include "Rendering/Mesh.h"
#include "Rendering/Shader.h"

#define ML_GLSL_VERSION "#version 130"

namespace MLEngine
{
    class Engine;
    class ResourceManager;
    class GraphicsContext;
    class Window;
    class Logger;

    extern Engine* gEngine;

    class Engine
    {
    public:

        void HandleCameraInputs(float delta_time);
        Engine();

        ~Engine();
        void RegisterInputEventCallbacks();

        void Init();

        void Update();

        void ProcessEvent(void* appstate, SDL_Event* event);

        void Shutdown();

        bool ShouldQuit();

        inline void RequestShutdown(std::string reason = "Unknown")
        {
            ShutdownReason = std::move(reason);
            bShutdownRequested = true;
        };

        bool isPlaying = false;

    public:
        std::shared_ptr<Logger> default_logger = nullptr;
        std::shared_ptr<Window> default_window = nullptr;
        std::shared_ptr<GraphicsContext> default_gcontext = nullptr;
        std::shared_ptr<Shader> default_shader = nullptr;
        Console console;

        Mesh* cube_mesh = nullptr;
        Camera camera{{0, 0, -10},glm::vec3(0), 16.0 / 9.0, 45};

        uint64_t last_tick = 0;
        bool freeze_time = false;

        bool bShutdownRequested = false;
        std::string ShutdownReason{};
    };
}

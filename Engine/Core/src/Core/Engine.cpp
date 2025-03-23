//
// Created by Lama on 01/02/2025.
//
#include "Core/Engine.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL3/SDL.h>

#include "Core/ImGuiIntegration.h"
#include "Core/Window.h"
#include "Core/CreateCube.h"
#include "Inputs/InputModule.h"
#include "Logger/Module.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <Logger/Preprocessor.h>
#include <Logger/Logger.h>

#include "CoreInterfaces/ApplicationInterface.h"
#include "CoreInterfaces/ModuleLocator.h"
#include "Core/Time.h"

namespace MLEngine {
    Engine *gEngine = nullptr;

    Engine::Engine() {
    }

    Engine::~Engine() {
    }

    void Engine::RegisterInputEventCallbacks() {
        InputModule& inputModule = *ModuleLocator<InputModule>::Get();

        inputModule.SubscribeToEvent(SDL_EVENT_QUIT, [this](const SDL_Event *Event) {
            RequestShutdown("SDL_EVENT_QUIT");
        });
        inputModule.SubscribeToEvent(SDL_EVENT_KEY_DOWN, [this](const SDL_Event *Event) {
            if (Event->key.key == SDLK_ESCAPE) {
                RequestShutdown("SDL_EVENT_KEY_DOWN");
            }
        });


        inputModule.SubscribeToEvent(SDL_EVENT_KEY_DOWN, [](const SDL_Event *Event) {
            if (Event->key.scancode == SDL_SCANCODE_GRAVE) {
                gEngine->console.ToggleConsole();
            }
        });
    }

    class Test{};

    void Engine::Init(ApplicationInterface* application) {
        gEngine = this;
        ModuleLocator<InputModule>::Register();
        Handle<LoggerModule> loggerModule = ModuleLocator<LoggerModule>::Register();
        loggerModule->AddCallback(StdOutLogCallback);
        loggerModule->AddFile("log.txt");


        MLLogTrace("Initializing Engine");
        RegisterInputEventCallbacks();
        console.RegisterCommand("shutdown", "Shuts down the engine", [this]() { RequestShutdown("Shutdown command"); });
        console.RegisterCommand("toggleTime", "Toggle the time system", [this]() { freeze_time = !freeze_time; });
        loggerModule->AddCallback([&](const LogEvent* event)
        {
            console.Log(GetDefaultFormattedLogMessage(event));
        });
        SDL_SetAppMetadata("MLEngine", "0.0.1", "com.meisterlama.mlengine");
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_AUDIO)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed: %s", SDL_GetError());
        }

        default_window = MakeHandle<Window>("MLEngine");
        default_window->Open();
        default_gcontext = MakeHandle<GraphicsContext>(default_window->GetWindowHandle());

        MLInitImGui(default_gcontext.get(), default_window.get());

        current_application = application;
        current_application->Init();
    }

    void Engine::Update() {
        if (!freeze_time) { UpdateTime(); }

        Renderer *renderer = default_gcontext->GetRenderer();
        renderer->ClearScreen(0.1, 0.1, 0.1, 1.0);

        MLNewImGuiFrame();

        current_application->Update();
        console.RenderConsole();
        MLRenderImGui();
        default_gcontext->SwapBuffers();
        ModuleLocator<InputModule>::Get()->ResetRelativeMouseMotion();

    }

    void Engine::ProcessEvent(SDL_Event *event) {
        ModuleLocator<InputModule>::Get()->ProcessEvent(event);
        MLProcessInputImGui(event);
        default_window->ProcessEvent(event);
        current_application->ProcessEvent(event);
    }

    void Engine::Shutdown() {
        MLLogTrace("Shutting down Engine with reason : {}", ShutdownReason);
        current_application->Shutdown();
        MLShutdownImGui();
    }

    bool Engine::ShouldQuit() {
        if (bShutdownRequested) return true;
        if (default_window == nullptr) return true;
        return false;
    }
}

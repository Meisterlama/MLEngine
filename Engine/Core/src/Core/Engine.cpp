//
// Created by Lama on 01/02/2025.
//
#include "Core/Engine.h"

#include <imgui.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "Core/ImGUIIntegration.h"
#include "Core/Time.h"
#include "CoreInterfaces/ApplicationInterface.h"
#include "CoreInterfaces/ModuleLocator.h"
#include "Inputs/Module.h"
#include "Logger/Module.h"
#include "Platform/Module.h"
#include "Platform/Window.h"


namespace MLEngine
{
    Engine* s_engine = nullptr;

    void Engine::RegisterInputEventCallbacks()
    {
        InputModule& inputModule = *ModuleLocator<InputModule>::Get();

        inputModule.SubscribeToEvent(SDL_EVENT_QUIT, [this](const PlatformEvent* event)
        {
            RequestShutdown("SDL_EVENT_QUIT");
        });
        inputModule.SubscribeToEvent(SDL_EVENT_KEY_DOWN, [this](const PlatformEvent* event)
        {
            SDL_Event* sdl_event = static_cast<SDL_Event*>(event->Event);
            if (sdl_event->key.key == SDLK_ESCAPE)
            {
                RequestShutdown("SDL_EVENT_KEY_DOWN");
            }
        });


        inputModule.SubscribeToEvent(SDL_EVENT_KEY_DOWN, [](const PlatformEvent* event)
        {
            SDL_Event* sdl_event = static_cast<SDL_Event*>(event->Event);
            if (sdl_event->key.scancode == SDL_SCANCODE_GRAVE)
            {
                s_engine->console.ToggleConsole();
            }
        });
    }

    class Test
    {
    };

    void Engine::Init(ApplicationInterface* application)
    {
        s_engine = this;

        ModuleLocator<PlatformModule>::Register();
        ModuleLocator<PlatformModule>::Get()->Init();

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


        default_window = MakeHandle<Window>();
        default_window->Open("MLEngine");
        default_gcontext = MakeHandle<GraphicsContext>(default_window);

        MLInitImGui(default_gcontext.get(), default_window.get());

        current_application = application;
        current_application->Init();
    }

    void Engine::Update()
    {
        if (!freeze_time) { UpdateTime(); }

        Renderer* renderer = default_gcontext->GetRenderer();
        renderer->ClearScreen(0.1, 0.1, 0.1, 1.0);

        MLNewImGuiFrame();

        current_application->Update();
        console.RenderConsole();
        MLRenderImGui();
        default_gcontext->SwapBuffers();
        ModuleLocator<InputModule>::Get()->ResetRelativeMouseMotion();
    }

    void Engine::ProcessEvent(const PlatformEvent* event)
    {
        ModuleLocator<InputModule>::Get()->ProcessEvent(event);
        MLProcessInputImGui(event);
        default_window->ProcessEvent(event);
        current_application->ProcessEvent(event);
    }

    void Engine::Shutdown()
    {
        MLLogTrace("Shutting down Engine with reason : {}", ShutdownReason);
        current_application->Shutdown();
        MLShutdownImGui();
    }

    bool Engine::ShouldQuit()
    {
        if (bShutdownRequested) return true;
        if (default_window == nullptr) return true;
        return false;
    }
}

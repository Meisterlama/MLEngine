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
#include "Rendering/Module.h"


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

    void Engine::Init(Handle<ApplicationInterface> application)
    {
        s_engine = this;

        ModuleLocator<PlatformModule>::RegisterInit();
        ModuleLocator<InputModule>::RegisterInit();
        Handle<RenderingModule> renderingModule = ModuleLocator<RenderingModule>::RegisterInit();

        Handle<LoggerModule> loggerModule = ModuleLocator<LoggerModule>::RegisterInit();
        loggerModule->AddCallback(StdOutLogCallback);
        loggerModule->AddFile("log.txt");


        MLLogTrace("Initializing Engine");
        RegisterInputEventCallbacks();
        console.RegisterCommand("shutdown", "Shuts down the engine", [this]() { RequestShutdown("Shutdown command"); });
        console.RegisterCommand("toggleTime", "Toggle the time system", [this]() { freezeTime = !freezeTime; });
        loggerModule->AddCallback([&](const LogEvent* event)
        {
            console.Log(GetDefaultFormattedLogMessage(event));
        });


        defaultWindow = MakeHandle<Window>();
        defaultWindow->Open("MLEngine");
        renderingModule->InitGraphicsContext(defaultWindow);

        MLInitImGui(renderingModule->GetGraphicsContext(), defaultWindow);

        currentApplication = application;
        currentApplication->Init();
    }

    void Engine::Update()
    {
        if (!freezeTime) { UpdateTime(); }
        Handle<GraphicsContext> graphicsContext = ModuleLocator<RenderingModule>::Get()->GetGraphicsContext();
        Renderer* renderer = graphicsContext->GetRenderer();
        renderer->ClearScreen(0.1, 0.1, 0.1, 1.0);

        MLNewImGuiFrame();

        currentApplication->Update();
        console.RenderConsole();
        MLRenderImGui();
        graphicsContext->SwapBuffers();
        ModuleLocator<InputModule>::Get()->ResetRelativeMouseMotion();
    }

    void Engine::ProcessEvent(const PlatformEvent* event)
    {
        ModuleLocator<InputModule>::Get()->ProcessEvent(event);
        MLProcessInputImGui(event);
        defaultWindow->ProcessEvent(event);
        currentApplication->ProcessEvent(event);
    }

    void Engine::Shutdown()
    {
        MLLogTrace("Shutting down Engine with reason : {}", shutdownReason);
        currentApplication->Shutdown();
        MLShutdownImGui();
    }

    bool Engine::ShouldQuit()
    {
        if (shutdownRequested) return true;
        if (defaultWindow == nullptr) return true;
        return false;
    }
}

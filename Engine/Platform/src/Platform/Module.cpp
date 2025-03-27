//
// Created by lama on 23/03/25.
//
#include "Platform/Module.h"

#include <SDL3/SDL.h>

#include "Debug/Logger.h"

namespace MLEngine
{
    void PlatformModule::Init()
    {
        ModuleInterface::Init();
        SDL_SetAppMetadata("MLEngine", "0.0.1", "com.meisterlama.mlengine");
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_AUDIO))
        {
            MLLogError("SDL_Init failed: {}", SDL_GetError());
        }
    }

    void PlatformModule::Update()
    {
        ModuleInterface::Update();
    }

    void PlatformModule::Shutdown()
    {
        ModuleInterface::Shutdown();
    }
}

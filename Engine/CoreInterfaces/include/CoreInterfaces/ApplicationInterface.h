//
// Created by lama on 21/03/25.
//
#pragma once
#include <SDL3/SDL_events.h>

namespace MLEngine
{
    class ApplicationInterface
    {
    public:
        virtual ~ApplicationInterface() = default;
        virtual void Init() = 0;

        virtual void Update() = 0;
        virtual void ProcessEvent(SDL_Event* event) = 0;

        virtual void Shutdown() = 0;
    };
}

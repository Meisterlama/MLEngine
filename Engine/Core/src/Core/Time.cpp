//
// Created by Lama on 04/02/2025.
//
#include "Core/Time.h"

#include <cstdint>
#include <SDL3/SDL.h>

namespace MLEngine::Time
{
    double time = 0.0f;
    uint64_t ticks = 0.0f;

    float deltaTime = 0.0f;
}

void MLEngine::UpdateTime()
{
    Time::ticks++;
    const double new_time = SDL_GetTicksNS() / 1'000'000'000.0f;
    Time::deltaTime = new_time - Time::time;
    Time::time = new_time;
}

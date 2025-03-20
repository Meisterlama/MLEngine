//
// Created by Lama on 04/02/2025.
//
#pragma once
#include <cstdint>

namespace MLEngine {
    void UpdateTime();

    namespace Time {
        extern double time;
        extern uint64_t ticks;
        extern float deltaTime;
    }
}

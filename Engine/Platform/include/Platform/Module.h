//
// Created by lama on 23/03/25.
//
#pragma once
#include "CoreInterfaces/ModuleInterface.h"

namespace MLEngine {
    class PlatformModule : ModuleInterface {
        public:
            PlatformModule() : ModuleInterface(){};
            ~PlatformModule() override = default;
            void Init() override;
            void Update() override;
            void Shutdown() override;
    };
}
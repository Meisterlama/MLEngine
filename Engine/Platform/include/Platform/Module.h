//
// Created by lama on 23/03/25.
//
#pragma once
#include "CoreInterfaces/ModuleInterface.h"

namespace MLEngine {
    class PlatformModule : public ModuleInterface {
        public:
            PlatformModule() : ModuleInterface("Platform"){};
            ~PlatformModule() override = default;
            void Init() override;
            void Update() override;
            void Shutdown() override;
    };
}
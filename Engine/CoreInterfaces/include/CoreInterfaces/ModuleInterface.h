//
// Created by lama on 21/03/25.
//
#pragma once
#include <SDL3/SDL_events.h>

#define DEFINE_MODULE(Module) ::MLEngine::ModuleInterfaceInstance<Module>::Instance;


namespace MLEngine {
    class ModuleInterface {
    public:
        ModuleInterface() = default;
        ModuleInterface(const ModuleInterface&) = delete;
        virtual ~ModuleInterface() = default;

        virtual void Init(){};

        virtual void Update(){};
        virtual void ProcessEvent(SDL_Event* event){};

        virtual void Shutdown(){};

        bool IsInitialized() const { return bInitialized; }
    protected:
        ModuleInterface& operator=(const ModuleInterface&) = default;
    private:
        bool bInitialized = false;
    };
}
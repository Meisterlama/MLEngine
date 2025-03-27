//
// Created by lama on 21/03/25.
//
#pragma once

#include "Debug/Assert.h"
#include "Debug/Logger.h"

namespace MLEngine
{
    struct PlatformEvent;
    class ModuleInterface
    {
    public:
        ModuleInterface(const char* name) : name(name) {}
        ModuleInterface(const ModuleInterface&) = delete;

        virtual ~ModuleInterface()
        {
            ML_ASSERT(!bInitialized, "Module {} was not destroyed during Engine lifetime, Undefined behaviour",
                      name);
            MLLogInfo("Shutting down {}", name);
            if (bInitialized)
            {
                ModuleInterface::Shutdown();
            }
        }

        //TODO: Support initialization arguments
        virtual void Init()
        {
            MLLogInfo("Initializing {}", name);
            bInitialized = true;
        };

        virtual void Update() {};

        virtual void ProcessEvent(const PlatformEvent* event) {};

        virtual void Shutdown()
        {
            bInitialized = false;
        };

        bool IsInitialized() const { return bInitialized; }

    protected:
        ModuleInterface& operator=(const ModuleInterface&) = default;
        const char* name = "Undefined";

    private:
        bool bInitialized = false;
    };
}

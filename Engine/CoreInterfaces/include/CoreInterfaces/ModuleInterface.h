//
// Created by lama on 21/03/25.
//
#pragma once

namespace MLEngine
{
    struct PlatformEvent;

    class ModuleInterface
    {
    public:
        ModuleInterface() = default;
        ModuleInterface(const ModuleInterface&) = delete;
        virtual ~ModuleInterface()
        {
            if (bInitialized)
            {
                ModuleInterface::Shutdown();
            }
        }

        //TODO: Support initialization arguments
        virtual void Init()
        {
            bInitialized = true;
        };

        virtual void Update()
        {
        };

        virtual void ProcessEvent(const PlatformEvent* event)
        {
        };

        virtual void Shutdown()
        {
            bInitialized = false;
        };

        bool IsInitialized() const { return bInitialized; }

    protected:
        ModuleInterface& operator=(const ModuleInterface&) = default;

    private:
        bool bInitialized = false;
    };
}

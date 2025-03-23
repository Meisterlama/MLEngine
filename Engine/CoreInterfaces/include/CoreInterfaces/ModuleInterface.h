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
        virtual ~ModuleInterface() = default;

        virtual void Init()
        {
        };

        virtual void Update()
        {
        };

        virtual void ProcessEvent(const PlatformEvent* event)
        {
        };

        virtual void Shutdown()
        {
        };

        bool IsInitialized() const { return bInitialized; }

    protected:
        ModuleInterface& operator=(const ModuleInterface&) = default;

    private:
        bool bInitialized = false;
    };
}

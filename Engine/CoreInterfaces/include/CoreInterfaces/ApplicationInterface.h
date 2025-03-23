//
// Created by lama on 21/03/25.
//
#pragma once
namespace MLEngine
{
    struct PlatformEvent;

    class ApplicationInterface
    {
    public:
        virtual ~ApplicationInterface() = default;
        virtual void Init() = 0;

        virtual void Update() = 0;
        virtual void ProcessEvent(const PlatformEvent* event) = 0;

        virtual void Shutdown() = 0;
    };
}

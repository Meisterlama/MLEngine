//
// Created by lama on 22/03/25.
//
#pragma once
#include "CoreInterfaces/ModuleInterface.h"
#include "Rendering/Context.h"

namespace MLEngine
{
    class RenderingModule : public ModuleInterface
    {
    public:
        RenderingModule() : ModuleInterface() {};
        ~RenderingModule() override = default;

        void Init() override;
        void Update() override;
        void Shutdown() override;

        void InitGraphicsContext(const Handle<Window>& window);

        Handle<GraphicsContext> GetGraphicsContext()
        {
            return graphicsContext;
        }

    private:
        Handle<GraphicsContext> graphicsContext;
    };
}

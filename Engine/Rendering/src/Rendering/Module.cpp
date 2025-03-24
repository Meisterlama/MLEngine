//
// Created by lama on 24/03/25.
//
#include "Rendering/Module.h"

namespace MLEngine {
    void RenderingModule::Init()
    {
        ModuleInterface::Init();
    }

    void RenderingModule::Update()
    {
        ModuleInterface::Update();
    }

    void RenderingModule::Shutdown()
    {
        ModuleInterface::Shutdown();
    }

    void RenderingModule::InitGraphicsContext(const Handle<Window>& window)
    {
        graphicsContext = MakeHandle<GraphicsContext>(window);
    }
}

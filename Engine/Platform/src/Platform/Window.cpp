//
// Created by lama on 23/03/25.
//
#include "Platform/Window.h"
#include "Platform/WindowHandle.h"
#include "Platform/Private/WindowImpl.h"

namespace MLEngine
{
    void Window::Open(const std::string& name)
    {
        windowImpl = MakeHandle<WindowImpl>();
        windowImpl->Open(name);
    }

    void Window::Close()
    {
        if (windowImpl)
        {
            windowImpl->Close();
            windowImpl = nullptr;
        }
    }

    void Window::ProcessEvent(const PlatformEvent* event)
    {
        windowImpl->ProcessEvent(event);
    }

    WindowHandle Window::GetWindowHandle() const
    {
        return windowImpl->GetWindowHandle();
    }
}

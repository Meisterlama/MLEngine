//
// Created by lama on 23/03/25.
//
#pragma once
#include <string>

#include "CoreInterfaces/Types.h"
#include "Platform/PlatformEvent.h"
#include "Platform/WindowHandle.h"

namespace MLEngine
{
    class WindowImpl;

    class Window
    {
    public:
        Window() = default;
        ~Window() { Close(); };

        void Open(const std::string& name);
        void Close();

        void ProcessEvent(const PlatformEvent* event);

        WindowHandle GetWindowHandle() const;

    private:
        Handle<WindowImpl> windowImpl;
    };
}

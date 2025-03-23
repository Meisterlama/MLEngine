//
// Created by lama on 23/03/25.
//
#pragma once
#include "Platform/Window.h"

#include <string>
#include <SDL3/SDL_video.h>

namespace MLEngine
{
    class WindowImpl
    {
    public:
        friend class Window;

        WindowImpl() = default;
        ~WindowImpl();

        void Open(const std::string& title);
        void Close();

        void ProcessEvent(const PlatformEvent* event);

        WindowHandle GetWindowHandle();

    private:
        SDL_Window* window_handle = nullptr;
    };
}

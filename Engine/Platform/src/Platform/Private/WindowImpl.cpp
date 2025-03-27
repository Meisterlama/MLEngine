//
// Created by lama on 23/03/25.
//
#include "Platform/Private/WindowImpl.h"

#include <SDL3/SDL_events.h>

#include "Debug/Logger.h"

namespace MLEngine
{
    WindowImpl::~WindowImpl()
    {
        Close();
    }

    void WindowImpl::Open(const std::string& title)
    {
        const SDL_WindowFlags window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;

        window_handle = SDL_CreateWindow(title.c_str(), 1920, 1080, window_flags);

        if (!window_handle)
        {
            MLLogError("Failed to create window: {}", SDL_GetError());
        }

        SDL_SetWindowPosition(window_handle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        SDL_ShowWindow(window_handle);
    }

    void WindowImpl::Close()
    {
        SDL_DestroyWindow(window_handle);
    }

    void WindowImpl::ProcessEvent(const PlatformEvent* event)
    {
        SDL_Event* sdl_event = static_cast<SDL_Event*>(event->Event);

        if (sdl_event->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED
            && sdl_event->window.windowID == SDL_GetWindowID(window_handle))
        {
            Close();
        }
    }

    WindowHandle WindowImpl::GetWindowHandle()
    {
        WindowHandle handle{};
        handle.Window = window_handle;
        return handle;
    }
}

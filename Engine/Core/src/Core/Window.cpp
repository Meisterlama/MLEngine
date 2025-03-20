//
// Created by Lama on 01/02/2025.
//
#include "Core/Window.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_messagebox.h>

#include "Core/Engine.h"


namespace MLEngine
{
    class Engine;

    Window::Window(const char* name) : Name(name) { }

    Window::~Window() { if (window_handle) { Close(); } }

    void Window::Open()
    {
        SDL_WindowFlags window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;

        window_handle = SDL_CreateWindow(Name.c_str(), 1920, 1080, window_flags);

        if (!window_handle)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window: %s", SDL_GetError());
        }

        SDL_SetWindowPosition(window_handle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        SDL_ShowWindow(window_handle);

        bOpened = true;
    }

    void Window::Close()
    {
        SDL_DestroyWindow(window_handle);

        bOpened = false;
    }

    void Window::ProcessEvent(SDL_Event* event)
    {
        if (!bOpened) return;
        if (event->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
            event->window.windowID == SDL_GetWindowID(window_handle)) { Close(); }
    }
}

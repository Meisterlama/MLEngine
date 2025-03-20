//
// Created by Lama on 01/02/2025.
//
#pragma once

#include <imgui_internal.h>
#include <string>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

namespace MLEngine {
    class Window {
    public:
        Window(const char *name);

        ~Window();

        void Open();

        void Close();

        void *GetWindowHandle() const { return window_handle; };

        void ProcessEvent(SDL_Event *event);

    private:
        std::string Name;
        SDL_Window *window_handle = nullptr;
        bool bOpened = false;
    };
}

//
// Created by Lama on 02/02/2025.
//
#pragma once

#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

#include "Window.h"
#include "Rendering/Context.h"

namespace MLEngine
{
    inline void MLInitImGui(GraphicsContext *Context, Window *Window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        ImGui::StyleColorsDark();

        ImGui_ImplSDL3_InitForOpenGL(static_cast<SDL_Window *>(Window->GetWindowHandle()), Context->GetContextHandle());
        ImGui_ImplOpenGL3_Init("#version 130");
    }

    inline void MLShutdownImGui()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
    }

    inline void MLNewImGuiFrame()
    {
        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
    }

    inline void MLProcessInputImGui(SDL_Event* Event)
    {
        ImGui_ImplSDL3_ProcessEvent(Event);
    }

    inline void MLRenderImGui()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}


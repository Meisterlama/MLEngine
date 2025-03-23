//
// Created by Lama on 02/02/2025.
//
#pragma once

#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

#include "Platform/Window.h"
#include "Rendering/Context.h"

namespace MLEngine
{
    inline void MLInitImGui(GraphicsContext* Context, const Window* Window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        ImGui::StyleColorsDark();;
        ImGui_ImplSDL3_InitForOpenGL(static_cast<SDL_Window*>(Window->GetWindowHandle().Window), Context->GetContextHandle());
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

    inline void MLProcessInputImGui(const PlatformEvent* event)
    {
        const SDL_Event* sdl_event = static_cast<SDL_Event*>(event->Event);
        ImGui_ImplSDL3_ProcessEvent(sdl_event);
    }

    inline void MLRenderImGui()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

#ifndef IMGUI_DISABLE
namespace ImGui
{
    // ImGui::InputText() with std::string
    // Because text input needs dynamic resizing, we need to setup a callback to grow the capacity
    IMGUI_API bool InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0,
                             ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);

    IMGUI_API bool InputTextMultiline(const char* label, std::string* str, const ImVec2& size = ImVec2(0, 0),
                                      ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr,
                                      void* user_data = nullptr);

    IMGUI_API bool InputTextWithHint(const char* label, const char* hint, std::string* str,
                                     ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr,
                                     void* user_data = nullptr);
}
#endif

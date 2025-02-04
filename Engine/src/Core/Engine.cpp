//
// Created by Lama on 01/02/2025.
//
#include "../../include/Core/Engine.h"

#include <algorithm>
#include <filesystem>

#include "Core/InputManager.h"
#include "Window.h"

#include <imgui.h>
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <filesystem>
#include "ImGUIIntegration.h"
#include "Core/CreateCube.h"
#include "Core/Logger.h"
#include <glm/gtc/matrix_transform.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "Core/Time.h"
#include "glm/detail/type_quat.hpp"

namespace MLEngine
{
    static unsigned int VAO, VBO;

    static bool show_demo_window = false;

    Engine* gEngine = nullptr;


    void Engine::HandleCameraInputs(float delta_time)
    {
        constexpr float camera_speed = 2.5f;
        constexpr float camera_sensitivity = 60.0f;

        InputManager& inputManager = InputManager::GetInstance();
        glm::vec3 position = camera.GetPosition();
        glm::vec3 rotation = camera.GetRotation();

        glm::vec3 relative_motion{0};
        if (inputManager.IsMouseButtonPressed(SDL_BUTTON_RIGHT))
        {
            // Handle Camera Movement
            if (inputManager.IsKeyPressed(SDL_SCANCODE_W))
                relative_motion.z += camera_speed * delta_time; // Move camera forward
            if (inputManager.IsKeyPressed(SDL_SCANCODE_S))
                relative_motion.z -= camera_speed * delta_time; // Move camera backward
            if (inputManager.IsKeyPressed(SDL_SCANCODE_A))
                relative_motion.x += camera_speed * delta_time; // Move camera left
            if (inputManager.IsKeyPressed(SDL_SCANCODE_D))
                relative_motion.x -= camera_speed * delta_time; // Move camera right
            if (inputManager.IsKeyPressed(SDL_SCANCODE_Q))
                relative_motion.y += camera_speed * delta_time; // Move camera up
            if (inputManager.IsKeyPressed(SDL_SCANCODE_E))
                relative_motion.y -= camera_speed * delta_time; // Move camera down
            relative_motion = glm::quat(glm::radians(rotation)) * relative_motion;


            glm::vec2 relMotion = inputManager.GetMouseRelMotion();
            rotation.y -= relMotion.x * camera_sensitivity *
                    delta_time; // Rotate camera left/right based on horizontal mouse movement
            rotation.x -= relMotion.y * camera_sensitivity *
                    delta_time; // Rotate camera up/down based on vertical mouse movement
        }
        camera.SetPosition(position + relative_motion);
        camera.SetRotation(rotation);
    }

    Engine::Engine() { }

    Engine::~Engine() { }

    void Engine::RegisterInputEventCallbacks()
    {
        InputManager::GetInstance().SubscribeToEvent(SDL_EVENT_QUIT, [this](const SDL_Event& Event)
        {
            RequestShutdown("SDL_EVENT_QUIT");
        });
        InputManager::GetInstance().SubscribeToEvent(SDL_EVENT_KEY_DOWN, [this](const SDL_Event& Event)
        {
            if (Event.key.key == SDLK_ESCAPE)
            {
                RequestShutdown("SDL_EVENT_KEY_DOWN");
            }
        });
        InputManager::GetInstance().SubscribeToEvent(SDL_EVENT_MOUSE_BUTTON_DOWN, [this](const SDL_Event& Event)
        {
            if (Event.button.button == SDL_BUTTON_RIGHT)
            {
                SDL_SetWindowRelativeMouseMode(
                    static_cast<SDL_Window*>(default_window->
                        GetWindowHandle()), true);
            }
        });
        InputManager::GetInstance().SubscribeToEvent(SDL_EVENT_MOUSE_BUTTON_UP, [this](const SDL_Event& Event)
        {
            if (Event.button.button == SDL_BUTTON_RIGHT)
            {
                SDL_SetWindowRelativeMouseMode(
                    static_cast<SDL_Window*>(default_window->
                        GetWindowHandle()), false);
            }
        });

        InputManager::GetInstance().SubscribeToEvent(SDL_EVENT_KEY_DOWN, [](const SDL_Event& Event)
        {
            if (Event.key.key == SDLK_F1)
            {
                show_demo_window = !show_demo_window;
            }
        });

        InputManager::GetInstance().SubscribeToEvent(SDL_EVENT_KEY_DOWN, [](const SDL_Event& Event)
        {
            if (Event.key.scancode == SDL_SCANCODE_GRAVE)
            {
                gEngine->console.ToggleConsole();
            }
        });
    }

    void Engine::Init()
    {
        gEngine = this;
        default_logger = std::make_shared<Logger>();
        SDL_Log("Initializing Engine");
        RegisterInputEventCallbacks();
        console.RegisterCommand("shutdown", "Shuts down the engine", [this]() { RequestShutdown("Shutdown command"); });
        console.RegisterCommand("toggleTime", "Toggle the time system", [this]() { freeze_time = !freeze_time; });

        SDL_SetAppMetadata("MLEngine", "0.0.1", "com.meisterlama.mlengine");
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_AUDIO))
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed: %s", SDL_GetError());
        }

        default_window = std::make_shared<Window>("MLEngine");
        default_window->Open();

        default_gcontext = std::make_shared<GraphicsContext>(default_window.get());

        default_shader = std::make_shared<Shader>("Assets/shaders/lighting.vert.glsl",
                                                  "Assets/shaders/lighting.frag.glsl");

        LoadOBJFile("Assets/cube.obj", cube_mesh);

        MLInitImGui(default_gcontext.get(), default_window.get());
    }

    void Engine::Update()
    {
        if (!freeze_time) { UpdateTime(); }

        HandleCameraInputs(MLEngine::Time::deltaTime);
        Renderer* renderer = default_gcontext->GetRenderer();
        renderer->ClearScreen(0.1, 0.1, 0.1, 1.0);

        glm::vec3 lightPos(2 * SDL_cos(1.0f * Time::time),
                           2 * SDL_cos(2.0f * Time::time),
                           2 * SDL_sin(1.0f * Time::time));

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
        // glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::vec3(0.5f));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
        default_shader->Use();
        default_shader->SetUniform("model", translate * scale);
        default_shader->SetUniform("lightPos", lightPos);
        default_shader->SetUniform("viewPos", camera.GetPosition());
        default_shader->SetUniform("lightColor", glm::vec3(1.0f, 0.0f, 1.0f));
        default_shader->SetUniform("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));

        renderer->DrawMesh(cube_mesh, default_shader.get(), &camera);
        translate = glm::translate(glm::mat4(1.0f), lightPos);
        scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
        default_shader->SetUniform("model", translate * scale);
        renderer->DrawMesh(cube_mesh, default_shader.get(), &camera);

        MLNewImGuiFrame();

        if (show_demo_window) { ImGui::ShowDemoWindow(); }
        console.RenderConsole();

        MLRenderImGui();

        default_gcontext->SwapBuffers();
        InputManager::GetInstance().ResetRelativeMouseMotion();
    }

    void Engine::ProcessEvent(void* appstate, SDL_Event* event)
    {
        InputManager::GetInstance().OnEvent(*event);
        MLProcessInputImGui(event);
        default_window->ProcessEvent(event);
    }

    void Engine::Shutdown()
    {
        SDL_Log("Shutting down Engine with reason : %s", ShutdownReason.c_str());
        MLShutdownImGui();
    }

    bool Engine::ShouldQuit()
    {
        if (bShutdownRequested) return true;
        if (default_window == nullptr) return true;
        return false;
    }
}

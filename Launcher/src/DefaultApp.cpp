#include "DefaultApp.h"

#include <glm/detail/type_quat.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Core/CreateCube.h"
#include "Core/Engine.h"
#include "Core/ImGUIIntegration.h"
#include "Core/Time.h"
#include "CoreInterfaces/ModuleLocator.h"
#include "Inputs/Module.h"
#include "Platform/EntryPoint.h"
#include "Rendering/Camera.h"
#include "Rendering/Context.h"
#include "Rendering/Module.h"
#include "Rendering/Shader.h"

Handle<MLEngine::ApplicationInterface> MLEngine::CreateApplication()
{
    return MakeHandle<DefaultApp>();
}

static unsigned int VAO, VBO;
static bool show_demo_window = false;

void DefaultApp::HandleCameraInputs(float delta_time)
{
    constexpr float camera_speed = 2.5f;
    constexpr float camera_sensitivity = 60.0f;

    MLEngine::InputModule& inputManager = *MLEngine::ModuleLocator<MLEngine::InputModule>::Get();
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

void DefaultApp::Init()
{
    MLEngine::InputModule& inputModule = *MLEngine::ModuleLocator<MLEngine::InputModule>::Get();
    inputModule.SubscribeToEvent(SDL_EVENT_MOUSE_BUTTON_DOWN, [this, &inputModule](const MLEngine::PlatformEvent* event)
    {
        SDL_Event* sdl_event = static_cast<SDL_Event*>(event->Event);
        if (sdl_event->button.button == SDL_BUTTON_RIGHT)
        {
            inputModule.SetCaptureMouse(true);
        }
    });
    inputModule.SubscribeToEvent(SDL_EVENT_MOUSE_BUTTON_UP, [this, &inputModule](const MLEngine::PlatformEvent* event)
    {
        SDL_Event* sdl_event = static_cast<SDL_Event*>(event->Event);
        if (sdl_event->button.button == SDL_BUTTON_RIGHT)
        {
            inputModule.SetCaptureMouse(false);
        }
    });

    inputModule.SubscribeToEvent(SDL_EVENT_KEY_DOWN, [](const MLEngine::PlatformEvent* event)
    {
        SDL_Event* sdl_event = static_cast<SDL_Event*>(event->Event);
        if (sdl_event->key.key == SDLK_F1)
        {
            show_demo_window = !show_demo_window;
        }
    });

    default_shader = std::make_shared<MLEngine::Shader>("Assets/shaders/lighting.vert.glsl",
                                                        "Assets/shaders/lighting.frag.glsl");

    LoadOBJFile("Assets/cube.obj", cube_mesh);
}

void DefaultApp::Update()
{
    HandleCameraInputs(MLEngine::Time::deltaTime);
    glm::vec3 lightPos(2 * SDL_cos(1.0f * MLEngine::Time::time),
                    2 * SDL_cos(2.0f * MLEngine::Time::time),
                    2 * SDL_sin(1.0f * MLEngine::Time::time));

    static glm::vec3 model_pos = glm::vec3(0.0f);
    static glm::vec3 model_rot = glm::vec3(0.0f);
    static glm::vec3 model_scale = glm::vec3(1.0f);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), model_pos);
    glm::quat rotationQuat = glm::quat(glm::radians(model_rot));
    glm::mat4 rotationMat = glm::mat4_cast(rotationQuat);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), model_scale);
    default_shader->Use();
    default_shader->SetUniform("model", translate * rotationMat * scale);
    default_shader->SetUniform("lightPos", lightPos);
    default_shader->SetUniform("viewPos", camera.GetPosition());
    default_shader->SetUniform("lightColor", glm::vec3(1.0f, 0.0f, 1.0f));
    default_shader->SetUniform("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));

    auto renderer = MLEngine::ModuleLocator<MLEngine::RenderingModule>::Get()->GetGraphicsContext()->GetRenderer();

    renderer->DrawMesh(cube_mesh, default_shader.get(), &camera);
    translate = glm::translate(glm::mat4(1.0f), lightPos);
    scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
    default_shader->SetUniform("model", translate * scale);
    renderer->DrawMesh(cube_mesh, default_shader.get(), &camera);



    if (show_demo_window) { ImGui::ShowDemoWindow(); }
    ImGui::Begin("Mesh Vec");
    ImGui::DragFloat3("Model Position", &model_pos.x, 0.01f);
    ImGui::DragFloat3("Model Rotation", &model_rot.x, 0.01f);
    ImGui::DragFloat3("Model Scale", &model_scale.x, 0.01f);
    ImGui::End();
}

void DefaultApp::ProcessEvent(const MLEngine::PlatformEvent* event)
{
}

void DefaultApp::Shutdown()
{
}

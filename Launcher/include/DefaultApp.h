//
// Created by lama on 20/03/25.
//
#pragma once
#include <memory>
#include "CoreInterfaces/ApplicationInterface.h"
#include "Core/Engine.h"
#include "Rendering/Camera.h"

namespace MLEngine
{

    class Camera;
    class Mesh;
    class Shader;
}

class DefaultApp : public MLEngine::ApplicationInterface
{
public:
    DefaultApp();

    void HandleCameraInputs(float delta_time);
    void Init() override;
    void Update() override;
    void Shutdown() override;
    void ProcessEvent(SDL_Event* event) override;

private:
    std::shared_ptr<MLEngine::Shader> default_shader = nullptr;
    MLEngine::Mesh* cube_mesh = nullptr;
    MLEngine::Mesh* random_mesh = nullptr;
    MLEngine::Camera camera{{0, 0, -10}, glm::vec3(0), 16.0 / 9.0, 45};
;
};

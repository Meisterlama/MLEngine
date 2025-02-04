//
// Created by Lama on 03/02/2025.
//
#pragma once
#include <glm/glm.hpp>

namespace MLEngine
{
    class Camera
    {
    public:
        Camera(glm::vec3 position, glm::vec3 rotation, float aspectRatio, float fov = 45.0f);
        ~Camera();

        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;

        void SetPosition(const glm::vec3& newPosition);
        void SetRotation(const glm::vec3& newRotation);
        void SetTarget(const glm::vec3& newTarget);

        const glm::vec3& GetPosition() const { return position; }

        const glm::vec3& GetRotation() const { return rotation; }

        float GetFOV() const { return fov; }

        float GetAspectRatio() const { return aspectRatio; }

    private:
        glm::vec3 position;
        glm::vec3 rotation;
        float fov;
        float aspectRatio;

        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;

        void UpdateViewMatrix();
        void UpdateProjectionMatrix();
    };
}

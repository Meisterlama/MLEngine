//
// Created by Lama on 03/02/2025.
//
#include "Rendering/Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glm/gtc/quaternion.hpp"

namespace MLEngine
{
    Camera::Camera(glm::vec3 position, glm::vec3 rotation, float aspectRatio, float fov)
        : position(position), rotation(rotation), fov(fov), aspectRatio(aspectRatio)
    {
        UpdateViewMatrix();
        UpdateProjectionMatrix();
    }

    Camera::~Camera() { }

    glm::mat4 Camera::GetViewMatrix() const { return viewMatrix; }

    glm::mat4 Camera::GetProjectionMatrix() const { return projectionMatrix; }

    void Camera::SetPosition(const glm::vec3& newPosition)
    {
        position = newPosition;
        UpdateViewMatrix();
    }

    void Camera::SetRotation(const glm::vec3& newRotation)
    {
        rotation = newRotation;
        UpdateViewMatrix();
    }

    void Camera::SetTarget(const glm::vec3& newTarget)
    {
        rotation = glm::eulerAngles(glm::quat(glm::lookAt(position, newTarget, glm::vec3(0.0f, 1.0f, 0.0f))));
        UpdateViewMatrix();
    }

    void Camera::UpdateViewMatrix()
    {
        // LookAt matrix: defines where the "eye" (camera) looks at.
        viewMatrix = glm::mat4(1.0f);

        glm::quat rotationQuat = glm::quat(glm::radians(rotation));
        glm::mat4 rotationMat = glm::mat4_cast(rotationQuat);
        glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), -position);
        viewMatrix = glm::inverse(translationMat * rotationMat);
    }

    void Camera::UpdateProjectionMatrix()
    {
        // Perspective projection with the given field of view, aspect ratio, and near/far planes
        projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
    }
}

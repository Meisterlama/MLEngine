//
// Created by Lama on 03/02/2025.
//
#pragma once

#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"

namespace MLEngine {
    class Renderer {
    public:
        Renderer();

        ~Renderer();

        void ClearScreen(float r, float g, float b, float a = 1.0f);

        void DrawMesh(const Mesh *mesh, const Shader *shader, const Camera *camera);

    private:
        void ConfigureGlobalStates();
    };
}

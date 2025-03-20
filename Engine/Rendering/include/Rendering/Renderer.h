//
// Created by Lama on 03/02/2025.
//
#pragma once

#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"

namespace MLEngine {
    class Renderer {
    public:
        Renderer();

        ~Renderer();

        void ClearScreen(float r, float g, float b, float a = 1.0f);

        void DrawMesh(Mesh *mesh, Shader *shader, Camera *camera);

    private:
        void ConfigureGlobalStates();
    };
}

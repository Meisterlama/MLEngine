//
// Created by Lama on 03/02/2025.
//
#include "Rendering/Renderer.h"
#include <glad/glad.h> // Ensure OpenGL functions are loaded
#include <SDL3/SDL_log.h>

namespace MLEngine
{
    Renderer::Renderer() { ConfigureGlobalStates(); }

    Renderer::~Renderer() { SDL_Log("Renderer destroyed"); }

    void Renderer::ClearScreen(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth
    }

    void Renderer::DrawMesh(Mesh* mesh, Shader* shader, Camera* camera)
    {
        shader->Use();

        // Set camera uniforms
        shader->SetUniform("view", camera->GetViewMatrix());
        shader->SetUniform("projection", camera->GetProjectionMatrix());

        mesh->Bind();

        // Render the mesh
        glDrawElements(GL_TRIANGLES, mesh->GetVertexCount(), GL_UNSIGNED_INT, 0);

        // Unbind the VAO
        glBindVertexArray(0);
    }

    void Renderer::ConfigureGlobalStates()
    {
        glEnable(GL_DEPTH_TEST); // Enable depth testing
        glEnable(GL_CULL_FACE);  // Enable face culling
        glCullFace(GL_BACK);     // Cull back faces
        SDL_Log("Global OpenGL states configured");
    }
}

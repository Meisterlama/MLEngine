//
// Created by Lama on 03/02/2025.
//


#include "Rendering/Mesh.h"
#include "Rendering/Shader.h"
#include <glad/glad.h>

namespace MLEngine
{
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
        : vertices(vertices), indices(indices) { SetupMesh(); }

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void Mesh::Bind() const
    {
        glBindVertexArray(VAO);
    }

    void Mesh::SetupMesh()
    {
        // Generate and bind VAO, VBO, and EBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        // Upload vertex data to the VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        // Upload index data to the EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // Position attribute
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));

        // Normal attribute
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));

        // TexCoords attribute
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoords));

        // Unbind the VAO to avoid accidental modification
        glBindVertexArray(0);
    }
}

//
// Created by Lama on 03/02/2025.
//
#pragma once
#include <vector>
#include <glm/glm.hpp>

namespace MLEngine
{
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    class Mesh {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
        ~Mesh();

        void Bind() const;

        size_t GetVertexCount() const { return indices.size(); }

    private:
        unsigned int VAO, VBO, EBO;
        void SetupMesh();

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
    };

}

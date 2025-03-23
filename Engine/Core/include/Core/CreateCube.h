//
// Created by Lama on 03/02/2025.
//

#pragma once
#include <tiny_obj_loader.h>

#include "Logger/Module.h"
#include "Rendering/Mesh.h"

namespace MLEngine
{
    inline bool LoadOBJFile(const std::string& filePath, Mesh*& mesh)
    {
        // TinyObjLoader required objects
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        // Load the OBJ file using tinyobjloader
        bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath.c_str());
        if (!warn.empty()) { MLLogWarn("Warning: {}", warn); }
        if (!err.empty()) { MLLogError("Error: {}", err); }
        if (!success)
        {
            MLLogError("Failed to load OBJ file: {}", filePath);
            return false;
        }

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        // Iterate over shapes (in .obj, each shape corresponds to a "mesh")
        for (const auto& shape : shapes)
        {
            size_t index_offset = 0;

            // Loop through all faces (polygons) in the shape
            for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++)
            {
                unsigned int fv = shape.mesh.num_face_vertices[f];
                // Number of vertices in the face (usually 3 for triangles)

                // Process each vertex of the face
                for (size_t v = 0; v < fv; v++)
                {
                    // Access the correct index in the face
                    tinyobj::index_t idx = shape.mesh.indices[index_offset + v];

                    // Create a Vertex instance and populate its fields:
                    Vertex vertex{};

                    // POSITION
                    vertex.position = glm::vec3(
                        attrib.vertices[3 * idx.vertex_index + 0],
                        attrib.vertices[3 * idx.vertex_index + 1],
                        attrib.vertices[3 * idx.vertex_index + 2]);

                    // NORMAL
                    if (idx.normal_index >= 0)
                    {
                        vertex.normal = glm::vec3(
                            attrib.normals[3 * idx.normal_index + 0],
                            attrib.normals[3 * idx.normal_index + 1],
                            attrib.normals[3 * idx.normal_index + 2]);
                    }
                    else
                    {
                        vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f); // Default normal if none is provided
                    }

                    // TEXTURE COORDINATES
                    if (idx.texcoord_index >= 0)
                    {
                        vertex.texCoords = glm::vec2(
                            attrib.texcoords[2 * idx.texcoord_index + 0],
                            attrib.texcoords[2 * idx.texcoord_index + 1]);
                    }
                    else
                    {
                        vertex.texCoords = glm::vec2(0.0f, 0.0f); // Default UV if none is provided
                    }

                    // Save the vertex
                    vertices.push_back(vertex);
                }

                // Add associated indices for the face's vertices
                for (size_t v = 0; v < fv; v++) { indices.push_back(index_offset + v); }

                index_offset += fv;
            }
        }

        // Create the Mesh object using the loaded data
        mesh = new Mesh(vertices, indices);
        return true;
    }
}

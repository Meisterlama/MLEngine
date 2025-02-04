#version 330 core

// Input from the vertex buffer object (VBO)
layout (location = 0) in vec3 aPos;      // Vertex position
layout (location = 1) in vec3 aNormal;  // Vertex normal
layout (location = 2) in vec2 aTexCoord; // Texture coordinates

// Matrices for transformations
uniform mat4 model;       // Model transformation matrix
uniform mat4 view;        // View transformation matrix
uniform mat4 projection;  // Projection transformation matrix

// Outputs to the fragment shader
out vec3 FragPos;         // Position of the vertex in world space
out vec3 Normal;          // Normal vector for lighting calculations
out vec2 TexCoord;        // Texture coordinates

void main() {
    // Apply transformations
    FragPos = vec3(model * vec4(aPos, 1.0)); // Transform position to world space
    Normal = mat3(transpose(inverse(model))) * aNormal; // Transform normal to world space
    TexCoord = aTexCoord; // Pass the texture coordinates

    // Calculate the final position in clip space
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
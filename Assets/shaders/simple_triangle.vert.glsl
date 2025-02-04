#version 330 core

// Input from the vertex attribute arrays
layout (location = 0) in vec3 aPos; // Vertex position

// Output to the fragment shader
void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); // Pass the position directly to clip space
}
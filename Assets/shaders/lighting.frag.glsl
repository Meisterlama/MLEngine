#version 330 core

// Outputs from the vertex shader
in vec3 FragPos;      // Position of the fragment in world space
in vec3 Normal;       // Normal vector for lighting
in vec2 TexCoord;     // Texture coordinates

// Output color
out vec4 FragColor;

// Uniforms for lighting
uniform vec3 lightPos;    // Position of the light
uniform vec3 viewPos;     // Position of the camera (viewer)
uniform vec3 lightColor;  // Color of the light
uniform vec3 objectColor; // Base color of the object

// Uniform for texture
uniform sampler2D ourTexture; // Texture sampler

void main() {
    // Ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting
    vec3 norm = normalize(Normal); // Make sure the normal is normalized
    vec3 lightDir = normalize(lightPos - FragPos); // Direction of the light
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular lighting (optional, adds shininess)
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos); // Direction towards viewer
    vec3 reflectDir = reflect(-lightDir, norm); // Reflect the light direction on the surface
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Combine lighting contributions
    vec3 lighting = (ambient + diffuse + specular);

    // Set the final fragment color
    FragColor = vec4(lighting, 1.0);
}
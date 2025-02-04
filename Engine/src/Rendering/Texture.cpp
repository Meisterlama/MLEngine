//
// Created by Lama on 03/02/2025.
//

#include "Rendering/Texture.h"
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

namespace MLEngine
{
    Texture::Texture(const std::string& filepath) { LoadTexture(filepath); }

    Texture::~Texture()
    {
        glDeleteTextures(1, &textureID);
    }

    void Texture::Bind(unsigned int slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot); // Activate the specified texture slot
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    void Texture::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::LoadTexture(const std::string& filepath)
    {
        // Generate and bind the texture
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Load image
        int width, height, numChannels;
        stbi_set_flip_vertically_on_load(true); // Flip textures vertically
        unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &numChannels, 0);

        if (data)
        {
            // Determine the format of the texture
            GLenum format = numChannels == 4 ? GL_RGBA : GL_RGB;

            // Upload texture data to the GPU
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            // Configure texture filtering and wrapping
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            std::cout << "Texture loaded: " << filepath << std::endl;
        } else { std::cerr << "Failed to load texture: " << filepath << std::endl; }

        stbi_image_free(data); // Free image data
        glBindTexture(GL_TEXTURE_2D, 0); // Unbind
    }
}

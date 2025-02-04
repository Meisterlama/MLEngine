//
// Created by Lama on 03/02/2025.
//
#pragma once
#include <string>

namespace MLEngine
{
    class Texture {
    public:
        Texture(const std::string& filepath);
        ~Texture();

        void Bind(unsigned int slot = 0) const;
        void Unbind() const;

    private:
        unsigned int textureID;
        void LoadTexture(const std::string& filepath);
    };
}

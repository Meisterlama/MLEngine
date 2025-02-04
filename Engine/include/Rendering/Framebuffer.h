//
// Created by Lama on 03/02/2025.
//
#pragma once

namespace MLEngine
{
    class Framebuffer {
    public:
        Framebuffer(unsigned int width, unsigned int height);
        ~Framebuffer();

        void Bind() const;
        void Unbind() const;

        unsigned int GetRenderTexture() const;

    private:
        unsigned int framebufferID;
        unsigned int renderTextureID;
        unsigned int depthBufferID;

        void Initialize(unsigned int width, unsigned int height);
    };

}
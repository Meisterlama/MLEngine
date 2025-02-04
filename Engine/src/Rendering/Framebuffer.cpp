//
// Created by Lama on 03/02/2025.
//
#include "Rendering/Framebuffer.h"
#include <glad/glad.h>
#include <iostream>

namespace MLEngine
{
    Framebuffer::Framebuffer(unsigned int width, unsigned int height) { Initialize(width, height); }

    Framebuffer::~Framebuffer()
    {
        glDeleteFramebuffers(1, &framebufferID);
        glDeleteTextures(1, &renderTextureID);
        glDeleteRenderbuffers(1, &depthBufferID);
    }

    void Framebuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
    }

    void Framebuffer::Unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    unsigned int Framebuffer::GetRenderTexture() const { return renderTextureID; }

    void Framebuffer::Initialize(unsigned int width, unsigned int height)
    {
        // Generate framebuffer
        glGenFramebuffers(1, &framebufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);

        // Generate color attachment (texture)
        glGenTextures(1, &renderTextureID);
        glBindTexture(GL_TEXTURE_2D, renderTextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTextureID, 0);

        // Generate depth attachment (renderbuffer)
        glGenRenderbuffers(1, &depthBufferID);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBufferID);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthBufferID);

        // Check if framebuffer is complete
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        }

        // Unbind framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}

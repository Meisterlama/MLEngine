//
// Created by Lama on 03/02/2025.
//
#pragma once
#include <string>
#include <glm/fwd.hpp>

namespace MLEngine {
    class Shader {
    public:
        Shader(const std::string &vertexPath, const std::string &fragmentPath);

        ~Shader();

        void Use() const;

        void SetUniform(const std::string &name, const glm::mat4 &value) const;

        void SetUniform(const std::string &name, const glm::vec3 &value) const;

        void SetUniform(const std::string &name, float value) const;

        void SetUniform(const std::string &name, int value) const;

    private:
        unsigned int programID;

        unsigned int CompileShader(unsigned int type, const std::string &source);

        void LinkProgram(unsigned int vertexShader, unsigned int fragmentShader);

        // Shader loading utility
        std::string ReadFile(const std::string &filepath);
    };
}

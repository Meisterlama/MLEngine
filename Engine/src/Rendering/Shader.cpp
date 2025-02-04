//
// Created by Lama on 03/02/2025.
//

#include "Rendering/Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace MLEngine
{
    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        std::string vertexCode = ReadFile(vertexPath);
        std::string fragmentCode = ReadFile(fragmentPath);

        // Compile shaders
        unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode);
        unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

        // Link shaders into a program
        LinkProgram(vertexShader, fragmentShader);

        // Delete the intermediate shader objects
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(programID);
    }

    void Shader::Use() const
    {
        glUseProgram(programID);
    }

    void Shader::SetUniform(const std::string& name, const glm::mat4& value) const
    {
        unsigned int loc = glGetUniformLocation(programID, name.c_str());
        glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
    }

    void Shader::SetUniform(const std::string& name, const glm::vec3& value) const
    {
        unsigned int loc = glGetUniformLocation(programID, name.c_str());
        glUniform3fv(loc, 1, &value[0]);
    }

    void Shader::SetUniform(const std::string& name, float value) const
    {
        unsigned int loc = glGetUniformLocation(programID, name.c_str());
        glUniform1f(loc, value);
    }

    void Shader::SetUniform(const std::string& name, int value) const
    {
        unsigned int loc = glGetUniformLocation(programID, name.c_str());
        glUniform1i(loc, value);
    }

    unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
    {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        // Check for errors
        int success;
        char infoLog[512];
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        return id;
    }

    void Shader::LinkProgram(unsigned int vertexShader, unsigned int fragmentShader)
    {
        programID = glCreateProgram();
        glAttachShader(programID, vertexShader);
        glAttachShader(programID, fragmentShader);
        glLinkProgram(programID);

        // Check for linking errors
        int success;
        char infoLog[512];
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(programID, 512, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM_LINKING_FAILED\n" << infoLog << std::endl;
        }
    }

    std::string Shader::ReadFile(const std::string& filepath)
    {
        std::ifstream file(filepath);
        std::stringstream buffer;

        if (file.is_open())
        {
            buffer << file.rdbuf();
            file.close();
        } else { std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << filepath << std::endl; }

        return buffer.str();
    }
}

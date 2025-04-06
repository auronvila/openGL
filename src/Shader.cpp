//
// Created by Auron Vila on 5.04.2025.
//
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include <GL/glew.h>
#include"Renderer.h"
#include "Shader.h"


Shader::Shader(const std::string &filepath): m_FilePath(filepath), m_RenderId(0) {
    ShaderProgramSource source = ParseShader(filepath);
    m_RenderId = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_RenderId));
}

void Shader::Bind() const {
    GLCall(glUseProgram(m_RenderId));
}

void Shader::UnBind() const {
    GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(GetUniformLocation(name),v0,v1,v2,v3));
}

unsigned int Shader::GetUniformLocation(const std::string &name) {
    if (m_uniformLocationChache.find(name) != m_uniformLocationChache.end()) {
        return m_uniformLocationChache[name];
    }
    GLCall(int location = glGetUniformLocation(m_RenderId,name.c_str()));
    if (location == -1) {
        std::cout << "Warning uniform!!!" << name << "doesn't exist" << std::endl;
    }
    m_uniformLocationChache[name] = location;
    return location;
}

unsigned int Shader::CreateShader(std::string &vertexShader, std::string &fragmentShader) {
    unsigned int program = glCreateProgram();

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source) {
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile" <<
                (type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader") << " !!!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

ShaderProgramSource Shader::ParseShader(const std::string &filePath) {
    std::ifstream stream(filePath);

    if (!stream.is_open()) {
        std::cerr << "Error: Unable to open shader file: " << filePath << std::endl;
        return {"", ""};
    }

    std::string line;
    std::stringstream ss[2];
    ShaderType shaderType = ShaderType::NONE;

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                shaderType = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                shaderType = ShaderType::FRAGMENT;
            }
        } else if (shaderType != ShaderType::NONE) {
            ss[static_cast<int>(shaderType)] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}

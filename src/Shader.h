//
// Created by Auron Vila on 5.04.2025.
//

#ifndef SHADER_H
#define SHADER_H
#include<string>
#include<unordered_map>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

enum class ShaderType {
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1,
};

class Shader {
private:
    unsigned int m_RenderId;
    std::string m_FilePath;
    std::unordered_map<std::string,int> m_uniformLocationChache;

public:
    Shader(const std::string &filepath);

    ~Shader();

    void Bind() const;

    void UnBind() const;

    // set uniforms
    void SetUniform4f(const std::string name, float v0, float v1, float v2, float v3);

private:
    unsigned int CompileShader(unsigned int type, const std::string &source);

    unsigned int CreateShader(std::string &vertexShader, std::string &fragmentShader);

    unsigned int GetUniformLocation(const std::string &name);

    ShaderProgramSource ParseShader(const std::string &filePath);
};

#endif //SHADER_H

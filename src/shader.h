#pragma once
#include <string>

struct ShaderProgramSource
{
    std::string VertexShaderSource;
    std::string FragmentShaderSource;
};


class Shader
{
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    // caching
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform4f(const std::string& name, float v0, float v1,float v2,float v3);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
private:
    ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    int GetUniformLocation(const std::string& name);
    
};

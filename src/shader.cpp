#include <iostream>
#include <fstream>
#include <sstream>

#include "shader.h"
#include "renderer.h"

Shader::Shader(const std::string& filepath)
    : m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexShaderSource,source.FragmentShaderSource);
    Bind();
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);
    
    enum class ShaderType {
        NONE     = -1,
        VERTAX   =  0,
        FRAGMENT =  1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream,line))
    {
        if (line == "// vert")
        {
            type = ShaderType::VERTAX;
        }
        else if (line == "// frag")
        {
            type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }
    return {
        ss[0].str(),
        ss[1].str()
    };
    
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    auto id = glCreateShader(type);
    auto typeName = type == GL_VERTEX_SHADER ? "vertex" : "fragment";
    const char* src = source.c_str();
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);

    int result;

    glGetShaderiv(id,GL_COMPILE_STATUS,&result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id,length,&length,message);
        std::cout << "Failed to Compile "<< typeName << "shader" << std::endl;
        std::cout << message << std::endl;

        std::cout << typeName << std::endl;
        std::cout << "```" << std::endl;
        std::cout << source << std::endl;
        std::cout << "```" << std::endl;
    }
    else
    {
    }
    
    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    auto program = glCreateProgram();
    auto vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    auto fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    int location = GetUniformLocation(name);
    GLCall(glUniform1i(location,value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    int location = GetUniformLocation(name);
    GLCall(glUniform1f(location,value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1,float v2,float v3)
{
    int location = GetUniformLocation(name);
    GLCall(glUniform4f(location,v0,v1,v2,v3));
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4 matrix)
{
    int location = GetUniformLocation(name);
    GLCall(glUniformMatrix4fv(location,1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name)
{

    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    GLCall(int location = glGetUniformLocation(m_RendererID ,name.c_str()))
    if (location == -1)
    {
        std::cout << "[Warning]: uniform '" << name << "' doesn't exist!" << std::endl;
    }
     
    m_UniformLocationCache[name] = location;
    
    return location;
}
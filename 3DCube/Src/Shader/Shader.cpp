#include "Shader.h"
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <iostream>

Shader::Shader(const std::string& filePath) : m_RendererID(0), filePath(filePath)
{
    auto [VertexSource, FragmentSource] = ParseShader(filePath);
    m_RendererID = CreateShader(VertexSource, FragmentSource);
    glUseProgram(m_RendererID);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::UnBind() const
{
    glUseProgram(0);
}

std::tuple<std::string, std::string> Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];

    ShaderType Type = ShaderType::NONE;


    while (std::getline(stream, line))
    {
        if (line.find("#Shader") != std::string::npos)
        {
            if (line.find("Vertex") != std::string::npos)
            {
                Type = ShaderType::VERTEX;
            }
            else if (line.find("Fragment") != std::string::npos)
            {
                Type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)Type] << line << '\n';
        }
    }

    return { ss[0].str() , ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int Type, const std::string& Source)
{
    unsigned int Id = glCreateShader(Type);
    const char* Src = Source.c_str();
    glShaderSource(Id, 1, &Src, nullptr);
    glCompileShader(Id);

    int Result;
    glGetShaderiv(Id, GL_COMPILE_STATUS, &Result);
    if (!Result)
    {
        int Length;
        glGetShaderiv(Id, GL_INFO_LOG_LENGTH, &Length);

        char* Message = (char*)alloca(Length * sizeof(char));

        glGetShaderInfoLog(Id, Length, &Length, Message);
        std::cout << "Failed To Compile" << (Type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "Shader!" << std::endl;
        std::cout << Message << std::endl;
        glDeleteShader(Id);
        return 0;
    }



    return Id;
}

int Shader::CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
{
    unsigned int Program = glCreateProgram();
    unsigned int Vs = CompileShader(GL_VERTEX_SHADER, VertexShader);
    unsigned int Fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

    glAttachShader(Program, Vs);
    glAttachShader(Program, Fs);

    glLinkProgram(Program);
    glValidateProgram(Program);

    glDeleteShader(Vs);
    glDeleteShader(Fs);

    return Program;
}

int Shader::GetUniformLocation(const std::string& Name) const
{
    if (m_CachedUniformLocation.find(Name) != m_CachedUniformLocation.end())
    {
        return m_CachedUniformLocation[Name];
    }
    else 
    {
        int Location = glGetUniformLocation(m_RendererID, Name.c_str());
        m_CachedUniformLocation[Name] = Location;
        return Location;
    }
}

void Shader::UpdateUniform4f(const std::string& Name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(Name), v0, v1, v2, v3);
}

void Shader::UpdateUniform1i(const std::string& Name, int Value)
{
    glUniform1f(GetUniformLocation(Name), Value);
}

void Shader::UpdateUniformMat4f(const std::string& Name, glm::mat4 matrix)
{
    glUniformMatrix4fv(GetUniformLocation(Name), 1, GL_FALSE, &matrix[0][0]);
}
void Shader::UpdateUniformVec3f(const std::string& Name, glm::vec3 vector)
{
    glUniform3f(GetUniformLocation(Name),vector.x,vector.y,vector.z);
};

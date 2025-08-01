#pragma once
#include <string>
#include "glm/glm.hpp"
#include <unordered_map>

class Shader
{
private:
	unsigned int m_RendererID;
	std::string filePath;
	mutable std::unordered_map<std::string, int> m_CachedUniformLocation;

public:

	Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	//Uniforms
	void UpdateUniform4f(const std::string& Name, float v0, float v1, float v2, float v3);
	void UpdateUniform1i(const std::string& Name, int Value);
	void UpdateUniformMat4f(const std::string& Name, glm::mat4 matrix);



private:

	//Shaders
	std::tuple<std::string, std::string> ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int Type, const std::string& Source);
	int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);

	//Uniforms
	int GetUniformLocation(const std::string& Name) const;
	


};

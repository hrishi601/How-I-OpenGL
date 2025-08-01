#pragma once
#include <GL/glew.h>
#include <vector>

struct Element {

	GLubyte Size;
	GLenum Type;
	GLboolean bNormalize;

};



class VertexBufferLayout {

public:

	VertexBufferLayout() : m_Elements(0), m_Stride(0) {};
	~VertexBufferLayout() {};

	void Push(GLubyte Size,GLenum Type,GLboolean bNormalize);
	

private:

	std::vector<Element> m_Elements;
	GLsizei m_Stride;

public:

	inline std::vector<Element> GetElemenets() const { return m_Elements; }
	inline GLsizei GetStride() const { return m_Stride; }

	static int GetSizeOfType(const GLenum& Type)
	{
		switch (Type)
		{
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_INT: return sizeof(GLint);
		default: return 0;
		}
	}

};

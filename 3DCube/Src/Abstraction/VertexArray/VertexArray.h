#pragma once
#include <GL/glew.h>


class VertexBuffer;
class IndexBuffer;
class VertexBufferLayout;


class VertexArray
{

public:

	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddBuffers(const VertexBuffer& Vb, const IndexBuffer& Ib, const VertexBufferLayout& Layout);

private:

	GLuint m_RendererID;
};


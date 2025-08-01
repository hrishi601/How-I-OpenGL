#pragma once
#include <GL/glew.h>
#include "ShapeData.h"

class VertexBuffer {

public:

	VertexBuffer(const ShapeData& ShapeData);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:

	GLuint m_RendererID;
};
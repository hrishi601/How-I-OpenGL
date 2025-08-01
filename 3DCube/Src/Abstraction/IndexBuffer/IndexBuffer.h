#pragma once
#include <GL/glew.h>
#include "ShapeData.h"


class IndexBuffer {

public:

	IndexBuffer(const ShapeData& ShapeData);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

private:

	GLuint m_RendererID;
};
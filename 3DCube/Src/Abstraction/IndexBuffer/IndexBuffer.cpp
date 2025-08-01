#include "IndexBuffer.h"


IndexBuffer::IndexBuffer(const ShapeData& ShapeData) : m_RendererID(0)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ShapeData.IndexBufferSize(), ShapeData.Indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{

}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

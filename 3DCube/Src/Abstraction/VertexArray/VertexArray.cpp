#include "VertexArray.h"
#include "VertexBuffer/VertexBuffer.h"
#include "IndexBuffer/IndexBuffer.h"
#include "VertexBufferLayout.h"
#include <vector>




VertexArray::VertexArray() : m_RendererID(0)
{
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray()
{
	
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffers(const VertexBuffer& Vb, const IndexBuffer& Ib, const VertexBufferLayout& Layout)
{
	Vb.Bind();
	Ib.Bind();
	auto Elements = Layout.GetElemenets();

	unsigned int offset = 0;

	for (int i = 0; i < Elements.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, Elements[i].Size, Elements[i].Type, Elements[i].bNormalize, Layout.GetStride(), (const void*)offset);
		offset += Elements[i].Size * VertexBufferLayout::GetSizeOfType(Elements[i].Type);
	}


}

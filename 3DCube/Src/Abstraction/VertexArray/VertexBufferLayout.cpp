#include "VertexBufferLayout.h"



void VertexBufferLayout::Push(GLubyte Size, GLenum Type, GLboolean bNormalize)
{
	m_Elements.push_back({ Size,Type,bNormalize });
	m_Stride += Size * GetSizeOfType(Type);
}

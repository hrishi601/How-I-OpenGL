#pragma once
#include "GL/glew.h"
#include "Vertex.h"

struct ShapeData
{
	ShapeData() : Vertices(nullptr), NumVertices(0), Indices(nullptr), NumIndices(0) {} ;

	Vertex* Vertices;
	GLuint NumVertices;

	GLushort* Indices;
	GLuint NumIndices;

	GLsizeiptr VertexBufferSize() const
	{
		return NumVertices * sizeof(Vertex);
	}

	GLsizeiptr IndexBufferSize() const
	{
		return NumIndices * sizeof(Vertex);
	}

	void CleanUp()
	{
		delete[] Vertices;
		delete[] Indices;
	}
	
};
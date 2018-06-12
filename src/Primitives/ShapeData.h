#pragma once
#include "Vertex.h"
#include "GL/glew.h"
typedef unsigned int uint;

struct ShapeData
{
	ShapeData() :
		vertices(0), numVertices(0),
		indices(0), numIndices(0) {}
	Vertex* vertices;
	uint numVertices;
	uint* indices;
	uint numIndices;
	GLsizeiptr vertexBufferSize() const
	{
		return numVertices * sizeof(Vertex);
	}
	GLsizeiptr indexBufferSize() const
	{
		return numIndices * sizeof(GLushort);
	}
	void cleanup()
	{
		delete [] vertices;
		delete [] indices;
		numVertices = numIndices = 0;
	}
};

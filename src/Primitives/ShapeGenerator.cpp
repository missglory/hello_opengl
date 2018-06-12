#include "ShapeGenerator.h"

//ShapeData ShapeGenerator::makeCube() {
//}



//ShapeData ShapeGenerator::generateNormals(const ShapeData& data)
//{
//	ShapeData ret;
//	ret.numVertices = data.numVertices * 2;
//	ret.vertices = new Vertex[ret.numVertices];
//	glm::vec3 white(1.0f, 1.0f, 1.0f);
//	for (int i = 0; i < data.numVertices; i++)
//	{
//		uint vertIndex = i * 2;
//		Vertex& v1 = ret.vertices[vertIndex];
//		Vertex& v2 = ret.vertices[vertIndex + 1];
//		const Vertex& sourceVertex = data.vertices[i];
//		v1.position = sourceVertex.position;
//		v2.position = sourceVertex.position + sourceVertex.normal;
//		v1.color = v2.color = white;
//	}
//
//	ret.numIndices = ret.numVertices;
//	ret.indices = new uint[ret.numIndices];
//	for (int i = 0; i < ret.numIndices; i++)
//		ret.indices[i] = i;
//	return ret;
//}

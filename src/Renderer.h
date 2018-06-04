#pragma once
#include "defines.h"
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

bool GlLogCall(const char* func, const char* file, int line);

class Renderer {
private:
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
#pragma once
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
class VertexArray {
private:
	uint renderer_id;
public:
	VertexArray();
	~VertexArray();
	void Bind() const;
	void Unbind() const;
	void AddBuffer(VertexBuffer& vb, VertexBufferLayout& layout);
};
#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void * data, unsigned int size)
{
	GlCall(glGenBuffers(1, &renderer_id));
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, renderer_id));	
	GlCall(glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GlCall(glDeleteBuffers(1, &renderer_id));
}

void VertexBuffer::Bind() const
{
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, renderer_id));
}

void VertexBuffer::Unbind() const
{
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

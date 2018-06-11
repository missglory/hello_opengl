#include "IndexBuffer.h"
#include "Renderer.h"	

//simple abstraction of IB
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):
	count(count)
{
	GlCall(glGenBuffers(1, &renderer_id));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id));	
	GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GlCall(glDeleteBuffers(1, &renderer_id));

}

void IndexBuffer::Bind() const
{
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id));
}

void IndexBuffer::Unbind() const
{
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

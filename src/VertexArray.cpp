#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	GlCall(glGenVertexArrays(1, &renderer_id));
}

VertexArray::~VertexArray()
{
	GlCall(glDeleteVertexArrays(1, &renderer_id));
}

void VertexArray::Bind() const {
	GlCall(glBindVertexArray(renderer_id));
}

void VertexArray::Unbind() const {
	GlCall(glBindVertexArray(0));
}


void VertexArray::AddBuffer(VertexBuffer& vb, VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const VBElems& elems = layout.GetElems();
	unsigned int offset = 0;
	for (int i = 0; i < elems.size(); i++) {
		const VBElem& elem = elems[i];
					
		GlCall(glVertexAttribPointer(i, elem.count, elem.type, elem.normalized, layout.GetStride(), (const void*)offset));
		GlCall(glEnableVertexAttribArray(i));
		offset += elem.count * VBElem::SizeOfType(elem.type);
	}
}

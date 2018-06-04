#include "Renderer.h"

#include <iostream>
bool GlLogCall(const char* func, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << file << ":[OpenGL error]line " << line << ": ";
		printf("0x%02x\n", error);
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	va.Bind();
	ib.Bind();
	shader.Bind();
	GlCall(glDrawElements(GL_TRIANGLES, (ib.GetCount()), GL_UNSIGNED_INT, nullptr));
}

#pragma once
#include "defines.h"
#include <vector>

struct VBElem {
	uint type;
	uint count;
	unsigned char normalized;
	VBElem(uint t, uint c, unsigned char n) : type(t), count(c), normalized(n) {}
	static unsigned int SizeOfType(uint type) {
		switch (type) {
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}
};

typedef std::vector<VBElem> VBElems;

class VertexBufferLayout {
private:
	VBElems elems;
	unsigned int stride;
public:
	VertexBufferLayout() : stride(0) {}
	~VertexBufferLayout() {}
	template<typename T>
	void Push(unsigned int count) {
		static_assert(false);
	}
	template<>
	void Push<float>(unsigned int count) {
		elems.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += count * sizeof(GLfloat);
	}
	template<>
	void Push<unsigned int>(unsigned int count) {
		elems.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += count * sizeof(GLuint);
	}
	template<>
	void Push<unsigned char>(uint count) {
		elems.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		stride += count * sizeof(GLubyte);
	}
	inline unsigned int GetStride() const { return stride; }
	inline const VBElems& GetElems() const { return elems; }
};
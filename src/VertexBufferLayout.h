#pragma once
#include "defines.h"
#include <vector>


//helper struct for following class
struct VBElem {
	uint type;
	uint count;
	unsigned char normalized;
	VBElem(uint t, uint c, unsigned char n) : type(t), count(c), normalized(n) {}
	static unsigned int SizeOfType(uint type) {
		switch (type) {
			case GL_FLOAT: return sizeof(float);
			case GL_UNSIGNED_INT: return sizeof(uint);
			case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
		}
		ASSERT(false);
		return 0;
	}
};

typedef std::vector<VBElem> VBElems;

//keeper of layout structure
//VertexArray class shoult fill up AttribPointerArray with it's help
class VertexBufferLayout {
private:
	VBElems elems;
	unsigned int stride;
public:
	VertexBufferLayout() : stride(0) {}
	~VertexBufferLayout() {}
//	template<typename T>
//	void Push(unsigned int count) {
//		static_assert(false);
//	}
//	template<>
//	void Push<float>(unsigned int count) {
//		elems.push_back({ GL_FLOAT, count, GL_FALSE });
//		stride += count * sizeof(GLfloat);
//	}
//	template<>
//	void Push<unsigned int>(unsigned int count) {
//		elems.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
//		stride += count * sizeof(GLuint);
//	}
//	template<>
//	void Push<unsigned char>(uint count) {
//		elems.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
//		stride += count * sizeof(GLubyte);
//	}
    void PushFloat(uint count) {
        elems.push_back(VBElem( GL_FLOAT, count, GL_FALSE ));
        stride += count * sizeof(GLfloat);
    }
    void PushUint32(uint count) {
        elems.push_back(VBElem( GL_UNSIGNED_INT, count, GL_FALSE ));
        stride += count * sizeof(GLuint);
    }
    void PushUint8(uint count) {
        elems.push_back(VBElem( GL_UNSIGNED_BYTE, count, GL_TRUE ));
        stride += count * sizeof(GLubyte);
    }
	inline unsigned int GetStride() const { return stride; }
	inline const VBElems& GetElems() const { return elems; }
};

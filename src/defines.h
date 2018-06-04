#pragma once
#include "GL/glew.h"

#define ASSERT(x) if(!(x)) __debugbreak()
#define GlCall(x) while (glGetError() != GL_NO_ERROR);\
	x;\
	ASSERT(GlLogCall(#x, __FILE__, __LINE__))

typedef unsigned int uint;
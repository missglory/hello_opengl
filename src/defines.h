#pragma once
#include "GL/glew.h"
#include <iostream>

//debug macros & typedefs

//this one is MSVC specific


#if defined(unix) || defined(__unix) || defined (__unix__) || defined(__APPLE__)
#define _PREDEF_UNIX
#include <signal.h>
#endif

#if defined( _WIN32 )
#define ASSERT(x) if(!(x)) __debugbreak()
#elif defined (_PREDEF_UNIX)
    #define ASSERT(x) \
    if (!(x)) \
        raise(SIGTRAP)
#endif


#define GlCall(x) while (glGetError() != GL_NO_ERROR);\
	x;\
	ASSERT(GlLogCall(#x, __FILE__, __LINE__))


typedef unsigned int uint;

project (hello_opengl)
cmake_minimum_required(VERSION 3.0.0)

message("PROJECT " ${PROJECT_NAME}:)
message("BUILD DIR " ${CMAKE_CURRENT_BINARY_DIR})
message("SRC DIR " ${CMAKE_CURRENT_SOURCE_DIR})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC)
#message("SRC LIST: " ${SRC})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/stb STB)

message ("STB: " ${STB})
set(INCLUDEDIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${INCLUDEDIR})
include_directories(${INCLUDEDIR}/GLEW/include)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/stb)

find_package(OpenGL)
message("OPENGL FOUND " ${OPENGL_FOUND} " " ${OPENGL_GLU_FOUND})

add_executable(${PROJECT_NAME} ${SRC} ${STB})

find_library(GLEW glew32s HINTS ${INCLUDEDIR}/GLEW/lib/Release/x64)
find_library(LIBVC15 glfw3 HINTS ${INCLUDEDIR}/GLFW)
message("LIBS " ${GLEW} " " ${LIBVC15})

target_link_libraries(${PROJECT_NAME} ${GLEW} ${LIBVC15} 
					  ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
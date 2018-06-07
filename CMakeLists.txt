project (hello_opengl)
cmake_minimum_required(VERSION 3.0.0)

message("PROJECT " ${PROJECT_NAME}:)
message("BUILD DIR " ${CMAKE_CURRENT_BINARY_DIR})
message("SRC DIR " ${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DGLUE_STATIC)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC)
#message("SRC LIST: " ${SRC})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/stb STB)
set (IMGUIDIR ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/imgui-1.61)
aux_source_directory(${IMGUIDIR} IMGUI)
aux_source_directory(${IMGUIDIR}/examples/opengl3_example IMGUIEX)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Primitives PRIMITIVES)
message("IMGUI")
message(${IMGUI})
message("IMGUI EXAMPLES")
message(${IMGUIEX})


message ("STB: " ${STB})
set(INCLUDEDIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${INCLUDEDIR})
include_directories(${INCLUDEDIR}/GLEW/include)
include_directories(${IMGUIDIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Primitives)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/vendor)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/stb)

find_package(OpenGL)
message("OPENGL FOUND " ${OPENGL_FOUND} " " ${OPENGL_GLU_FOUND})

add_executable(${PROJECT_NAME} ${SRC} ${STB} ${IMGUI} ${IMGUIEX} ${PRIMITIVES})

if (UNIX)
    find_library(GLEW libGLEW.a HINTS ${INCLUDEDIR}/GLEW/lib/Release/Unix)
    find_library(LIBVC15 libglfw3.a HINTS ${INCLUDEDIR}/GLFW)
else()
    find_library(GLEW glew32s HINTS ${INCLUDEDIR}/GLEW/lib/Release/x64)
    find_library(LIBVC15 glfw3 HINTS ${INCLUDEDIR}/GLFW)
endif()

message("LIBS:")
message("GLEW " ${GLEW})
message("GLFW " ${LIBVC15})

target_link_libraries(${PROJECT_NAME} ${GLEW} ${LIBVC15} 
					  ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})

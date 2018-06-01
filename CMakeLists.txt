project (hello_opengl)

message("PROJECT " ${PROJECT_NAME}:)
message("BUILD DIR " ${CMAKE_CURRENT_BINARY_DIR})
message("SRC DIR " ${CMAKE_CURRENT_SOURCE_DIR})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC)
set(INCLUDEDIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
message ("INCLUDE DIR " ${INCLUDEDIR})
include_directories(${INCLUDEDIR})
include_directories("${INCLUDEDIR}/GLEW/include")

find_package(OpenGL)
message("OPENGL FOUND " ${OPENGL_FOUND} " " ${OPENGL_GLU_FOUND})

add_executable(${PROJECT_NAME} ${SRC})

find_library(GLEW glew32s HINTS ${INCLUDEDIR}/GLEW/lib/Release/x64)
find_library(LIBVC15 glfw3 HINTS ${INCLUDEDIR}/GLFW)
message("LIBS " ${GLEW} " " ${LIBVC15})

target_link_libraries(${PROJECT_NAME} ${GLEW} ${LIBVC15} 
					  ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
#define GLEW_STATIC
#include "defines.h"
#include "GL/glew.h"
#include "Renderer.h"
#include <GLFW/glfw3.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include <iostream>
#include "Texture.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/imgui-1.61/imgui.h"
#include "vendor/imgui-1.61/examples/opengl3_example/imgui_impl_glfw_gl3.h"
#include "Primitives/ShapeData.h"
#include "Primitives/ShapeGenerator.h"
#include "vendor/stb/stb_image.h"
using glm::mat4;
using glm::vec4;
using glm::vec3;
using glm::radians;
using glm::rotate;


void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	const int WIDTH = 1280;
	const int HEIGHT = 800;
	//set version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello cube", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//for resizing
	int framebufferWidth = 0, framebufferHeight = 0;
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "glewInit() error!\n";
	std::cout << glGetString(GL_VERSION) << "\n";

	//vertices & indices
	ShapeData cube = ShapeGenerator::makeCube();

	//set vertex buffer & layout for vertex array
	VertexArray va;

	//3 floats for positions & color & normal and 2 more for texCoords
	VertexBuffer vb(cube.vertices, cube.numVertices * sizeof(float) * 11);
	VertexBufferLayout layout;
	//push pointers for vertices & colors & normals & textureCoords
	//colors & normals are present but unused, I am lazy to clean them
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(3);
	va.AddBuffer(vb, layout);

	//enable blending
	GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GlCall(glEnable(GL_BLEND));

	//index buffer object
	IndexBuffer ib(cube.indices, cube.numIndices);

	float r = 0.0f;
	float incr = 2.5;

	// parse shader
	// ".." because I execute from build dir
	Shader shader("../res/shaders/basic.shader");
	
	//abstract texture loading as uniform with stbi
	Texture tx("../res/textures/crate.bmp");
	tx.Bind(0);
	shader.SetUniform1i("u_Texture", 0);
	//shader.SetUniform1i("cubeMap", cubemapID);

	//unbind everything 
	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();
	
	//init drawer
	Renderer render;
	
	//init ImGui
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, 1);
	ImGui::StyleColorsDark();

	//variables for ImGui
	glm::vec3 translation(0.0f, 0.0f, 0.0f);
	float rotation = 0.0f;
	float rotationManual = 0.0f;
	float persp = 60.0f;
	float viewParams[] = { 3.0f, 4.0f, -3.0f };
	


	//handle polygons depth problem
	GlCall(glEnable(GL_DEPTH_TEST));
	GlCall(glDepthFunc(GL_LESS));
	while (!glfwWindowShouldClose(window))
	{
		/* clear buffers each frame to update depth & colors */
		GlCall(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));

		//init ImGui frame
		ImGui_ImplGlfwGL3_NewFrame();	

		//MVP model 
		glm::mat4 projj = glm::perspective(glm::radians(persp), ((float)WIDTH) / (float)HEIGHT, 0.1f, 100.0f);
		glm::mat4 View = glm::lookAt(
			glm::vec3(viewParams[0], viewParams[1], viewParams[2]), // Camera is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		mat4 mvp = projj * View;
		
		mvp = glm::translate(mvp, glm::vec3(translation));
		mvp = glm::rotate(mvp, radians(rotationManual), vec3(0.0f, 1.0f, 0.0f));
		mvp = glm::rotate(mvp, radians(rotation), vec3(1.0f, 0.0f, 0.0f));
		rotation += incr;

		//bind shader and send uniforms
		shader.Bind();
		shader.SetUniformMat4f("mvp", mvp);
		shader.SetUniform1i("u_Texture", 0);
		//bind buffers & draw
		render.Draw(va, ib, shader);

		//ImGui frame
		{
            ImGui::SliderFloat3("translation", &translation.x, -7.0f, 7.0f);
			ImGui::SliderFloat3("view", viewParams, -10.0f, 10.0f);
			ImGui::SliderFloat("rotate", &rotationManual, -90.0f, 90.0f);
			ImGui::SliderFloat("persp", &persp, -100.0f, 100.0f);
            ImGui::Text("%.3f ms/f (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	//free everything
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}


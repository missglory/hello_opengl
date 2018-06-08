#define GLEW_STATIC
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
	int framebufferWidth = 0, framebufferHeight = 0;
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
	
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
	
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "glewInit() error!\n";
	std::cout << glGetString(GL_VERSION) << "\n";

	float positions[] = {
		-0.5f, -0.5f, 0.0f, 0.0f,
		 1.0f, 0.0f, 0.0f, 
		 0.5f, -0.5f, 1.0f, 0.0f,
		 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 1.0f, 1.0f,
		 0.0f, 0.0f, 1.0f,
		 -0.5f, 0.5f, 0.0f, 1.0f,
		 1.0f, 1.0f, 1.0f
	};

	float cubeVtx[] = {
		-1.0f, +1.0f, +1.0f,  // 0
		+1.0f, +0.0f, +0.0f,	// Color
		+0.0f, +1.0f, +0.0f,  // Normal
		+1.0f, +1.0f, +1.0f,  // 1
		+0.0f, +1.0f, +0.0f,	// Color
		+0.0f, +1.0f, +0.0f,  // Normal
		+1.0f, +1.0f, -1.0f,  // 2
		+0.0f, +0.0f, +1.0f,  // Color
		+0.0f, +1.0f, +0.0f,  // Normal
		-1.0f, +1.0f, -1.0f,  // 3
		+1.0f, +1.0f, +1.0f,  // Color
		+0.0f, +1.0f, +0.0f,  // Normal

		-1.0f, +1.0f, -1.0f,  // 4
		+1.0f, +0.0f, +1.0f,  // Color
		+0.0f, +0.0f, -1.0f,  // Normal
		+1.0f, +1.0f, -1.0f,  // 5
		+0.0f, +0.5f, +0.2f,  // Color
		+0.0f, +0.0f, -1.0f,  // Normal
		+1.0f, -1.0f, -1.0f,  // 6
		+0.8f, +0.6f, +0.4f,  // Color
		+0.0f, +0.0f, -1.0f,  // Normal
		-1.0f, -1.0f, -1.0f,  // 7
		+0.3f, +1.0f, +0.5f,  // Color
		+0.0f, +0.0f, -1.0f,  // Normal

		+1.0f, +1.0f, -1.0f,  // 8
		+0.2f, +0.5f, +0.2f,  // Color
		+1.0f, +0.0f, +0.0f,  // Normal
		+1.0f, +1.0f, +1.0f,  // 9
		+0.9f, +0.3f, +0.7f,  // Color
		+1.0f, +0.0f, +0.0f,  // Normal
		+1.0f, -1.0f, +1.0f,  // 10
		+0.3f, +0.7f, +0.5f,  // Color
		+1.0f, +0.0f, +0.0f,  // Normal
		+1.0f, -1.0f, -1.0f,  // 11
		+0.5f, +0.7f, +0.5f,  // Color
		+1.0f, +0.0f, +0.0f,  // Normal

		-1.0f, +1.0f, +1.0f,  // 12
		+0.7f, +0.8f, +0.2f,  // Color
		-1.0f, +0.0f, +0.0f,  // Normal
		-1.0f, +1.0f, -1.0f,  // 13
		+0.5f, +0.7f, +0.3f,  // Color
		-1.0f, +0.0f, +0.0f,  // Normal
		-1.0f, -1.0f, -1.0f,  // 14
		+0.4f, +0.7f, +0.7f,  // Color
		-1.0f, +0.0f, +0.0f,  // Normal
		-1.0f, -1.0f, +1.0f,  // 15
		+0.2f, +0.5f, +1.0f,  // Color
		-1.0f, +0.0f, +0.0f,  // Normal

		+1.0f, +1.0f, +1.0f,  // 16
		+0.6f, +1.0f, +0.7f,  // Color
		+0.0f, +0.0f, +1.0f,  // Normal
		-1.0f, +1.0f, +1.0f,  // 17
		+0.6f, +0.4f, +0.8f,  // Color
		+0.0f, +0.0f, +1.0f,  // Normal
		-1.0f, -1.0f, +1.0f,  // 18
		+0.2f, +0.8f, +0.7f,  // Color
		+0.0f, +0.0f, +1.0f,  // Normal
		+1.0f, -1.0f, +1.0f,  // 19
		+0.2f, +0.7f, +1.0f,  // Color
		+0.0f, +0.0f, +1.0f,  // Normal

		+1.0f, -1.0f, -1.0f,  // 20
		+0.8f, +0.3f, +0.7f,  // Color
		+0.0f, -1.0f, +0.0f,  // Normal
		-1.0f, -1.0f, -1.0f,  // 21
		+0.8f, +0.9f, +0.5f,  // Color
		+0.0f, -1.0f, +0.0f,  // Normal
		-1.0f, -1.0f, +1.0f,  // 22
		+0.5f, +0.8f, +0.5f,  // Color
		+0.0f, -1.0f, +0.0f,  // Normal
		+1.0f, -1.0f, +1.0f,  // 23
		+0.9f, +1.0f, +0.2f,  // Color
		+0.0f, -1.0f, +0.0f,  // Normal
	};

	//vertices & indices
	ShapeData cube = ShapeGenerator::makeCube();

	//set vertex buffer & layout
	VertexArray va;
	VertexBuffer vb(cubeVtx, sizeof(cubeVtx));
	VertexBufferLayout layout;
	//push pointers for vertices & colors & normals
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(3);
	va.AddBuffer(vb, layout);
	

	unsigned int indices[]{
		0, 1, 2,
		2, 3, 0

	};

	//enable blending
	GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GlCall(glEnable(GL_BLEND));
	
	//index buffer object
	IndexBuffer ib(cube.indices, cube.numIndices);

	float r = 0.0f;
	float incr = 0.05f;

	// parse vertex & fragment shaders
	// ".." because I execute from build dir
	Shader shader("../res/shaders/basic.shader");
	
	Texture tx("../res/textures/wp.bmp");
	tx.Bind(0);
	shader.SetUniform1i("u_Texture", 0);


	//unbind everything to ensure that abstractions work properly
	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();
	
	Renderer render;
	
	//init ImGui
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, 1);
	ImGui::StyleColorsDark();

	glm::vec3 translation(0.0f, 0.0f, 0.0f);

	glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.0f, 1.0f, -2.0f, 2.0f);
	//glm::mat4 proj(1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	float rotation = 1.0f;
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


		//matrices of MVP model 
		glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
		glm::mat4 projj = glm::perspective(glm::radians(persp), ((float)WIDTH) / (float)HEIGHT, 0.1f, 100.0f);
		glm::mat4 View = glm::lookAt(
			glm::vec3(viewParams[0], viewParams[1], viewParams[2]), // Camera is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		glm::mat4 rotate = glm::rotate(glm::mat4(), glm::radians(rotation), glm::vec3(1.0f, 0.0f, 0.0f));
		void* rotatep = &rotate[0][0];
		glm::mat4 transl = glm::translate(glm::mat4(1.0f), translation);
		//glm::mat4 modeln = proj * transl;
		glm::mat4 modeln = model * transl;
		glm::mat4 mvp = projj * transl * View; /* * model; */
		glm::mat4 projn = proj * projj;
		
		
		mvp = glm::rotate(mvp, radians(rotation), vec3(1.0f, 0.0f, 0.0f));
			
		//bind buffer and send uniforms
		shader.Bind();
		shader.SetUniformMat4f("mvp", mvp);
		shader.SetUniformMat4f("ortho", proj);
		shader.SetUniformMat4f("model", model);
		shader.SetUniformMat4f("proj", projj); 
		shader.SetUniform1f("u_Texture", 0);
		
		//bind buffers & draw
		render.Draw(va, ib, shader);

		//ImGui frame
		{
            ImGui::SliderFloat3("translation", &translation.x, -7.0f, 7.0f);
			ImGui::SliderFloat3("view", viewParams, -10.0f, 10.0f);
			ImGui::SliderFloat("rotate", &rotation, -180.f, 180.f);
			ImGui::SliderFloat("persp", &persp, -100.0f, 100.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
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


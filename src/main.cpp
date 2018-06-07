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
int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	float width = 640 * 2, 
		height = 480 * 2;
	window = glfwCreateWindow((int)width, (int)height, "Hello cube", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
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

	//unsigned int vao; //for core profile
	//GlCall(glGenVertexArrays(1, &vao));
	//GlCall(glBindVertexArray(vao));
	
	ShapeData cube = ShapeGenerator::makeCube();

	VertexArray va;
	//VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	VertexBuffer vb(cubeVtx, sizeof(cubeVtx));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(3);
	va.AddBuffer(vb, layout);
	

	unsigned int indices[]{
		0, 1, 2,
		2, 3, 0

	};
	GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GlCall(glEnable(GL_BLEND));
	//index buffer object
	IndexBuffer ib(cube.indices, cube.numIndices);

	float r = 0.0f;
	float incr = 0.05f;


	Shader shader("../res/shaders/basic.shader");
	
	Texture tx("../res/textures/wp.png");
	tx.Bind(0);
	shader.SetUniform1i("u_Texture", 0);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();
	Renderer render;

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, 1);
	ImGui::StyleColorsDark();

	glm::vec3 translation(0.0f, 0.0f, 0.0f);

	glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.0f, 1.0f, -2.0f, 2.0f);
	//glm::mat4 proj(1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	float rotation = 60.0f;
	float persp = 60.0f;
	float viewParams[] = { 3.0f, 4.0f, -3.0f };
	
	GlCall(glEnable(GL_DEPTH_TEST));
	GlCall(glDepthFunc(GL_LESS));
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		GlCall(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));

		ImGui_ImplGlfwGL3_NewFrame();	

		glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
		glm::mat4 projj = glm::perspective(glm::radians(persp), (float)width / (float)height, 0.1f, 100.0f);
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
		//shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
		shader.Bind();
		//shader.SetUniformMat4f("model", mvp);
		shader.SetUniformMat4f("mvp", mvp);
		shader.SetUniformMat4f("ortho", proj);
		shader.SetUniformMat4f("model", model);
		shader.SetUniformMat4f("proj", projj); 
		shader.SetUniform1f("u_Texture", 0);
		
		
		//va.Bind(); // 1.bind buffer
		////GlCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0));
		////GlCall(glEnableVertexAttribArray(0)); // 2. setup layout for buffer
		//
		//ib.Bind();
		render.Draw(va, ib, shader);


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
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}


#define GLEW_STATIC
#include "GL/glew.h"
#include "Renderer.h"
#include <GLFW/glfw3.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include <iostream>
#include "Texture.h"

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
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "glewInit() error!\n";
	std::cout << glGetString(GL_VERSION) << "\n";

	float positions[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, //0
		 0.5f, -0.5f, 1.0f, 0.0f, //1
		 0.5f,  0.5f, 1.0f, 1.0f, //2
		 -0.5f, 0.5f, 0.0f, 1.0f  //3
	};

	//unsigned int vao; //for core profile
	//GlCall(glGenVertexArrays(1, &vao));
	//GlCall(glBindVertexArray(vao));
	

	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	

	unsigned int indices[]{
		0, 1, 2,
		2, 3, 0
	};

	//index buffer object
	IndexBuffer ib(indices, 6 * sizeof(unsigned int));

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
	/* Loop until the user closes the window */
	Renderer render;
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		GlCall(glClear(GL_COLOR_BUFFER_BIT));

		//shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
		shader.Bind();
		//va.Bind(); // 1.bind buffer
		////GlCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0));
		////GlCall(glEnableVertexAttribArray(0)); // 2. setup layout for buffer
		//
		//ib.Bind();
		render.Draw(va, ib, shader);

		if (r > 1.0f) {
			incr = -0.05f;
		}
		else if (r < 0.0f) {
			incr = 0.05f;
		}
		r += incr;

		/*glBegin(GL_TRIANGLES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glEnd();*/


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


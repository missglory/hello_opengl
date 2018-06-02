#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define ASSERT(x) if(!(x)) __debugbreak()
#define GlCall(x) while (glGetError() != GL_NO_ERROR);\
	x;\
	ASSERT(GlLogCall(#x, __FILE__, __LINE__))

//static void GlClearError() {
//	while (glGetError());
//}

static bool GlLogCall(const char* func, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << file << ":[OpenGL error]line " << line << ": ";
		printf("0x%02x\n", error);
		return false;
	}
	return true;
}

struct ShaderSrc {
	std::string vertex, fragment;
};

static ShaderSrc parseShader(const std::string& filepath) {
	std::ifstream ifs(filepath);
	if (!ifs.is_open()) {
		std::cout << "error reading shaders from file!!!\n";
	}
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(ifs, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << "\n";
		}
	}
	return { ss[0].str(), ss[1].str() };
}

static unsigned int CreateShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char *src = source.c_str();
	GlCall(glShaderSource(id, 1, &src, nullptr));
	GlCall(glCompileShader(id));

	// TODO: Error handling
	int result;
	GlCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		int length;
		GlCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(sizeof(char) * length); // alloca for stack allocation dynamicly
		GlCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "failed to compile " 
			<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment") 
			<< " shader: " << message << "\n";
		GlCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

static int CreateShader(const std::string &vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CreateShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CreateShader(GL_FRAGMENT_SHADER, fragmentShader);

	GlCall(glAttachShader(program, vs));
	GlCall(glAttachShader(program, fs));
	GlCall(glLinkProgram(program));
	GlCall(glValidateProgram(program));
		  
	GlCall(glDeleteShader(vs));
	GlCall(glDeleteShader(fs));

	return program;
}


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "glewInit() error!\n";
	std::cout << glGetString(GL_VERSION) << "\n";

	float positions[] = {
		-0.5f, -0.5f, //0
		 0.5f, -0.5f, //1
		 0.5f,  0.5f, //2
		 -0.5f, 0.5f  //3
	};

	// init buffer
	unsigned int buffer;
	GlCall(glGenBuffers(1, &buffer));
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	GlCall(glBufferData(GL_ARRAY_BUFFER, 2 * 6 * sizeof(float), positions, GL_STATIC_DRAW));

	// initialise the layer for the buffer
	GlCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0));
	GlCall(glEnableVertexAttribArray(0));

	unsigned int indices[]{
		0, 1, 2,
		2, 3, 0
	};

	unsigned int ibo; //index buffer object
	GlCall(glGenBuffers(1, &ibo));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

	ShaderSrc shaderSrc = parseShader("../res/shaders/basic.shader");
	
	unsigned int shader = CreateShader(shaderSrc.vertex, shaderSrc.fragment);
	GlCall(glUseProgram(shader));
	 
	int location = glGetUniformLocation(shader, "u_Color");
	ASSERT(location != -1);
	GlCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f)); //rgba


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		GlCall(glClear(GL_COLOR_BUFFER_BIT));

		//glDrawArrays(GL_TRIANGLES, 0, 6);

		GlCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

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

	GlCall(glDeleteProgram(shader));
	glfwTerminate();
	return 0;
}


#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


#include "../Headers/Mesh.h"

// Callback function to resize the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
// Callback function to process input
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int width = 640;
int height = 480;
GLFWwindow* window;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"void main() \n"
"{\n"
"	gl_FragColor[0] = gl_FragCoord.x / 640.0;\n"
"	gl_FragColor[1] = gl_FragCoord.y / 480.0;\n"
"	gl_FragColor[2] = 0.8;\n"
"}\n\0";

void CreateShaderProgram()
{
	// Create the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
#pragma endregion
}
bool InitWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "OpenGL-POE", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW." << std::endl;
		return -1;
	}

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

}

int main()
{
	//GLM Test Stuff 
	/*glm::vec4 vec(1.0f, 1.0f, 1.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f); // identity matrix

	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f)); // Translation

	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0)); // Rotation
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5)); // Scale
	vec = trans * vec;
	std::cout << vec.x << ' ' << vec.y << ' ' << vec.z << std::endl;
	*/

	if (InitWindow()) // If the window was not created
		return -1;

	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		GLuint indices[] =
		{
			0, 2, 1,
			1, 3, 2,
			2, 3, 0,
			0, 1, 2
		};

		//array with GLfloats
		//points that make up the triangle
		GLfloat vertices[] =
		{
			//    x      y      z		 u	   v
				-1.0f, -1.0f, 0.0f,		0.0f, 0.0f,
				0.0f, -1.0f, 1.0f,		0.5f, 0.0f,
				1.0f, -1.0f, 0.0f,		1.0f, 0.0f,
				0.0f, 1.0f, 0.0f,		0.5f, 1.0f
		};
		//// Create the vertex buffer object
		//GLuint VBO;
		//glGenBuffers(1, &VBO);
		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

		//// Create the vertex array object
		//GLuint VAO;
		//glGenVertexArrays(1, &VAO);
		//glBindVertexArray(VAO);
		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
		
		Mesh* mesh = new Mesh();
		mesh->createMesh(vertices, indices, 20, 12);

		CreateShaderProgram();
		
		mesh->renderMesh();

		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(0);
		//glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// Check events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;



}

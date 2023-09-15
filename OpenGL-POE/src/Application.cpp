#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "../Headers/Shader.h"
#include "../Headers/VBO.h"
#include "../Headers/VAO.h"
#include "../Headers/IBO.h"


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
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,// Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,// Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,// Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Upper triangle
	5, 4, 1 // Lower right triangle
};

//Terrain Generation
void CreateTerrain()
{
	// load height map texture
	int width, height, nChannels;
	unsigned char* data = stbi_load("Height Map/Terrain.png",
		&width, &height, &nChannels,
		0);

	// vertex generation
	std::vector<float> vertices;
	float yScale = 64.0f / 256.0f, yShift = 16.0f;  // apply a scale+shift to the height data
	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
		{
			// retrieve texel for (i,j) tex coord
			unsigned char* texel = data + (j + width * i) * nChannels;
			// raw height at coordinate
			unsigned char y = texel[0];

			// vertex
			vertices.push_back(-height / 2.0f + i);        // v.x
			vertices.push_back((int)y * yScale - yShift); // v.y
			vertices.push_back(-width / 2.0f + j);        // v.z
		}
	}

	stbi_image_free(data);

	// index generation
	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i < height - 1; i++)       // for each row a.k.a. each strip
	{
		for (unsigned int j = 0; j < width; j++)      // for each column
		{
			for (unsigned int k = 0; k < 2; k++)      // for each side of the strip
			{
				indices.push_back(j + width * (i + k));
			}
		}
	}

	const unsigned int NUM_STRIPS = height - 1;
	const unsigned int NUM_VERTS_PER_STRIP = width * 2;

	// register VAO
	GLuint terrainVAO, terrainVBO, terrainEBO;
	glGenVertexArrays(1, &terrainVAO);
	glBindVertexArray(terrainVAO);

	glGenBuffers(1, &terrainVBO);
	glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
	glBufferData(GL_ARRAY_BUFFER,
		vertices.size() * sizeof(float),       // size of vertices buffer
		&vertices[0],                          // pointer to first element
		GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &terrainEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(unsigned int), // size of indices buffer
		&indices[0],                           // pointer to first element
		GL_STATIC_DRAW);

	// draw mesh
	glBindVertexArray(terrainVAO);
	// render the mesh triangle strip by triangle strip - each row at a time
	for (unsigned int strip = 0; strip < NUM_STRIPS; ++strip)
	{
		glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
			NUM_VERTS_PER_STRIP, // number of indices to render
			GL_UNSIGNED_INT,     // index data type
			(void*)(sizeof(unsigned int)
				* NUM_VERTS_PER_STRIP
				* strip)); // offset to starting index
	}
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
	
	
	glEnable(GL_DEPTH_TEST);
	//// Create the shader program
	Shader shaderProgram = Shader("Shaders/height.vert", "Shaders/height.frag");

	//// Create VAO, VBO, and IBO
	//VAO VAO1;
	//VAO1.Bind();
	//// Create the VBO and link to vertices
	//VBO VBO1(vertices, sizeof(vertices));
	//// Create the IBO and link to indices
	//IBO IBO1(indices, sizeof(indices));

	//VAO1.LinkVBO(VBO1, 0);
	//VAO1.Unbind();	
	//VBO1.Unbind();
	//IBO1.Unbind();

	CreateTerrain();

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// Rendering commands here
		// Clear the screen to a specific color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();
	
		
		//// Draw primitives, number of indices, datatype of indices, index of indices
		//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Check events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	

	

	glfwTerminate();
	return 0;



}

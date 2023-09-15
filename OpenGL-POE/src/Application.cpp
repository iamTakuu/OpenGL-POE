#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stb/stb_image.h>


#include "../Headers/Shader.h"
#include "../Headers/VBO.h"
#include "../Headers/VAO.h"
#include "../Headers/IBO.h"
#include "../Headers/Texture.h"

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

int width = 480;
int height = 480;
GLFWwindow* window;

bool InitWindow()
{
	glfwInit();

	// Set the major and minor versions of OpenGL that we want to use
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Set the profile of OpenGL that we want to use
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
	// X,	  Y,	 Z,		R,		G,		B		 U  ,   V
	-0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,	0.0f,	 0.0f, 0.0f,// Lower left vertex
	-0.5f,   0.5f,  0.0f,	0.0f,	1.0f,	0.0f,    0.0f, 1.0f,// Upper left vertex
	 0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	1.0f,    1.0f, 1.0f, // Upper right vertex
	 0.5f,	-0.5f,	0.0f,	1.0f,	1.0f,	1.0f,    1.0f, 0.0f // Lower right vertex
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Upper left triangle
	0, 2, 3  // Lower right triangle
};



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

	// Create the shader program
	Shader shaderProgram = Shader("Shaders/default.vert", "Shaders/default.frag");

	// Create VAO, VBO, and IBO
	VAO VAO1;
	VAO1.Bind();
	// Create the VBO and link to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Create the IBO and link to indices
	IBO IBO1(indices, sizeof(indices));
	// Takes in the layou, how many components per attrib (as in 3 for vert and col )
	// type of components,
	// stride, and offset
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0); // Vertex attributes
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Color attributes
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); // Texture coord attributes
	VAO1.Unbind();	
	VBO1.Unbind();
	IBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//// Texture stuff
	//GLint widthImg, heightImg, numColCh;
	//stbi_set_flip_vertically_on_load(true); // Flip the image on the y axis
	//unsigned char* bytes = stbi_load("Textures/pop_cat.png", &widthImg, &heightImg, &numColCh, 0);

	//GLuint texture;	
	//glGenTextures(1, &texture);
	//glActiveTexture(GL_TEXTURE0); // Activate the texture unit first before binding texture
	//glBindTexture(GL_TEXTURE_2D, texture); // Bind the texture to the texture unit

	//// Set the texture wrapping/filtering options (on the currently bound texture object)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // X axis
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Y axis

	//// float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f }; // Red border
	//// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	//// Load the image into the texture
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	//glGenerateMipmap(GL_TEXTURE_2D);

	//stbi_image_free(bytes);
	//glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

	//GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	//shaderProgram.Activate();
	//glUniform1i(tex0Uni, 0); // Set the texture unit to 0

	Texture popCat("Textures/pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);



	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// Rendering commands here
		// Clear the screen to a specific color
		glClearColor(0.09f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		// Set the uniform variable. Can be done after shaderProgram.Activate().
		glUniform1f(uniID, 0.5f); 

		popCat.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
		// Check events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	VAO1.Delete();
	VBO1.Delete();
	IBO1.Delete();
	shaderProgram.Delete();
	popCat.Delete();

	glfwTerminate();
	return 0;



}

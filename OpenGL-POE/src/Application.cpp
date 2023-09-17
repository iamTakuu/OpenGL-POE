
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Headers/Mesh.h"
#include "../Headers/Board.h"

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
// Window dimensions
const unsigned width = 800;
const unsigned int height = 800;
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

// Vertices coordinates
Vertex floorVertices[] =
{ //               COORDINATES           /            COLORS          /      TEXTURE COORDINATES    //
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),   glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f),   glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint floorIndices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex cubeVertices[] =
{
	//              COORDINATES           /            COLORS          /      TEXTURE COORDINATES    //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f),  glm::vec3(1.0f, 1.0f, 1.0f)},

	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f), glm::vec3(1.0f, 1.0f, 1.0f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f), glm::vec3(1.0f, 1.0f, 1.0f)}
};


GLuint cubeIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};



int main()
{
	if (InitWindow()) // If the window was not created
		return -1;

	//// Variable to store textures required for the mesh
	//Texture textures[] =
	//{
	//	// Leave textType blank for now, later we will use it to determine the type of texture.
	//	// Like diffuse, specular, etc.
	//	Texture("Textures/pop_cat.png", "", 0, GL_RGBA, GL_UNSIGNED_BYTE)
	//};
	//// Create the shader program
	Shader shaderProgram = Shader("Shaders/default.vert", "Shaders/default.frag");
 //	
	//std::vector <Vertex> verts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
	//std::vector <GLuint> ind(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
	//std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	//// Create cube mesh
	//Mesh cube(verts, ind, tex);
	////cubeVertices[0] = { glm::vec3(-0.1f, -0.1f,  0.1f), glm::vec3(1.0f, 1.0f, 1.0f) };
	//glm::vec3 cubePos = glm::vec3(-0.5f, 0.0f, 0.5f); // Position of the cube
	//glm::mat4 cubeModel = glm::mat4(1.0f); // Make sure to initialize matrix to identity matrix first
	//// Move model to the position of the cube
	//cubeModel = glm::translate(cubeModel, cubePos);

	//// Activate the shader program
	//shaderProgram.Activate();
	//// Get matrix's uniform location and set matrix
	//// Think of it as locking the model mat4 to the properties of the shader
	//// if you update model, it will update the shader
	//glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
	Board board(64, shaderProgram);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Camera
	Camera camera(width, height, glm::vec3(0.0f, -75.0f, 50.0f));

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// Rendering commands here
		// Clear the screen to a specific color
		//glClearColor(0.09f, 0.13f, 0.17f, 1.0f);
		//Clear color to black (not really necessary actually since we are drawing a background image)
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Also clear the depth buffer now!



		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		camera.Input(window);


		/* glm::mat4 model = glm::mat4(1.0f); // Make sure to initialize matrix to identity matrix first
		glm::mat4 view = glm::mat4(1.0f); // Make sure to initialize matrix to identity matrix first
		glm::mat4 projection = glm::mat4(1.0f); // Make sure to initialize matrix to identity matrix first

		// Rotate the model in the y axis
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		// 0.1f is near plane and 100.f is far plane (clipping)
		// FOV is 45 degrees...needs to be in rads
		projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.f);

		// Get matrix's uniform location and set matrix
		// Think of it as locking the model mat4 to the properties of the shader
		// if you update model, it will update the shader
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection)); */

		// Draw the mesh
		//cube.Draw(shaderProgram, camera);
		board.Draw(shaderProgram,camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	

	shaderProgram.Delete();


	glfwTerminate();
	return 0;



}

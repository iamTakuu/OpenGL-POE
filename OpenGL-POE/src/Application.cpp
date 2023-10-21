
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Headers/Mesh.h"
#include "../Headers/Board.h"
#include "../Headers/Cube.h"
#include "../Headers/Terrain.h"
#include "../Headers/Sphere.h"
#include "../Headers/Cylinder.h"
#include "../Headers/Pawn.h"

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
const unsigned width = 1280;
const unsigned int height = 720;
GLFWwindow* window;

bool InitWindow()
{
	glfwInit();

	// Set the major and minor versions of OpenGL that we want to use
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Set the profile of OpenGL that we want to use
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	window = glfwCreateWindow(width, height, "POE - Chess Demo", NULL, NULL);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return true;
	}
	glfwMakeContextCurrent(window);
	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW." << std::endl;
		return true;
	}

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return false;
}

int main()
{
	if (InitWindow()) // If the window was not created
		return -1;

	Shader default_shader = Shader("Shaders/default.vert", "Shaders/default.frag");
	//Shader terrainShader = Shader("Shaders/height.vert", "Shaders/height.frag");
	// Create the mesh for the Chess Board
	Board board(64, default_shader);
	// Move the board to the center of the screen
	board.parent_model = glm::translate(board.parent_model, glm::vec3(0.0f, 0.0f, 0.0f));

	
	//Terrain terrain("HeightMap/Terrain2.png");
	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Camera
	Camera camera(width, height, glm::vec3(-1.5f, 0.0f, 80.0f));
	//terrain.Draw(terrainShader, camera);
	camera.initMatrix(20.0f, 0.1f, 100.0f);
	camera.rotateMatrix(0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	
	Pawn pawn(5.0f, 0.0f, 2.0f, 1.5f, 16, 16);
	Pawn pawn2(5.0f, 0.0f, 2.0f, 1.5f, 16, 16);
	pawn.setNewPosition(glm::vec3(-7.0f, 4.0f, 1.5f));
	pawn2.setNewPosition(glm::vec3(-2.0f, 0.0f, 1.5f));

	Texture texture = Texture("Textures/white.png", "", 0, GL_RGB, GL_UNSIGNED_BYTE);
	Cube cube(texture);
	cube.transform.setLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	//pawn2.set
	//pawn.Position = glm::vec3(-8.0f, 0.0f, 5.0f);
	//pawn.Rotation = glm::rotate( pawn.Rotation, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//pawn.Scale = glm::vec3(0.6f, 0.6f, 0.6f);
	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// ******************************* Rendering commands here ******************************************************
		// Clear the screen to a specific color

		//Clear color to black (not really necessary actually since we are drawing a background image)
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Also clear the depth buffer now!

		

		//camera.updateMatrix(20.0f, 0.1f, 100.0f);
		camera.Input(window);
		// Draw the mesh

		pawn.Render(default_shader, camera);
		pawn2.Render(default_shader, camera);
		//board.Draw(default_shader,camera);
		cube.Render(default_shader, camera);
		


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	

	default_shader.Delete();


	glfwTerminate();
	return 0;



}

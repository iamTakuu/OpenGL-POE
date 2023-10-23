
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Headers/Bishop.h"
#include "../Headers/Rook.h"
#include "../Headers/Mesh.h"
#include "../Headers/Board.h"
#include "../Headers/King.h"
#include "../Headers/Knight.h"
#include "../Headers/Terrain.h"
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

	window = glfwCreateWindow(width, height, "POE - Chess Demo", nullptr, nullptr);
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
	Board board(64);
	
	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Camera
	Camera camera(width, height, glm::vec3(-1.5f, 0.0f, 80.0f));
	camera.initMatrix(20.0f, 0.1f, 150.0f);
	camera.rotateMatrix(0.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	PawnProps pawn_props =
		{
		5.0f,
		0.0f,
		2.0f,
		1.5f,
		16,
		16
		};
	// Create a vector of 8 pawns
	std::vector<Pawn> white_pawns;
	std::vector<Pawn> black_pawns;
	
	for (size_t i = 0; i < 8; i++)
	{
		white_pawns.emplace_back(pawn_props, true);
		white_pawns[i].setScale(glm::vec3(0.6f, 0.6f, 0.6f));
		white_pawns[i].setPosition(glm::vec3(-4.5f + (1.3f * i), 1.3f, 2.0f));

		black_pawns.emplace_back(pawn_props, false);
		black_pawns[i].setScale(glm::vec3(0.6f, 0.6f, 0.6f));
		black_pawns[i].setPosition(glm::vec3(-4.5f + (1.3f * i), 1.3f, -4.5f));
	}
		
	//****** Good Starting Position ********
	//pawn.setPosition(glm::vec3(-4.4f, 1.3f, 3.0f));


	RookProps rook_props =
	{
		1.8f,
		2.5f,
		9.0f,
		1.0f,
		3.0f,
		1.0f,
		3.5f,
		16,
		16
	};
		
	Rook rook(rook_props, true);
	rook.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	rook.setPosition(glm::vec3(-4.8f, .8f, -3.0f));
	
	BishopProps bishop_props =
	{
		1.8f,
		0.8f,
		2.5f,
		10.0f,
		1.0f,
		3.0f,
		2.5f,
		3.0f,
		16,
		16
	};

	Bishop bishop(bishop_props, false);
	bishop.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	bishop.setPosition(glm::vec3(4.8f, .8f, 0.0f));

	KingProps king_props =
	{
		1.5f,
		2.5f,
		15.0f,
		1.0f,
		2.0f,
		2.5f,
		3.0f,
		16,
		16
	};

	King king(king_props, false);
	king.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	king.setPosition(glm::vec3(-2.0f, .8f, 0.0f));
	
	KnightProps knight_props =
	{
		12.0f,
		0.8f,
		2.5f,
		2.5f,
		3.0f,
		16,
		16,
	};
	Knight knight(knight_props, false);
	knight.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	knight.setPosition(glm::vec3(-4.8f, .9f, 0.5f));
	//knight.setRotation(glm::vec3(0.0f, 45.0f, 0.0f));

	Terrain terrain("Textures/terrain.png");
	terrain.transform.setLocalScale(glm::vec3(0.5f, 0.5f, 0.5f));
	terrain.transform.setLocalPosition(glm::vec3(0.0f, -6.0f, 0.0f));
	
	
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// ******************************* Rendering commands here ******************************************************
		// Clear the screen to a specific color

		//Clear color to black (not really necessary actually since we are drawing a background image)
		glClearColor(0.1f, 0.1f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Also clear the depth buffer now!
		
		//camera.updateMatrix(20.0f, 0.1f, 100.0f);
		camera.Input(window);
		// Render the mesh
		 board.Draw(default_shader, camera);
		 for (auto pawn : white_pawns)
		 {
		 	pawn.Render(default_shader, camera);
		 }
		 for (auto pawn : black_pawns)
		 {
		 	pawn.Render(default_shader, camera);
		 }
		rook.Render(default_shader, camera);
		bishop.Render(default_shader, camera);
		knight.Render(default_shader, camera);
		king.Render(default_shader, camera);
		terrain.Render(default_shader, camera);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	default_shader.Delete();
	
	glfwTerminate();
	return 0;



}

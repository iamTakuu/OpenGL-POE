#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
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
#include "../Headers/Queen.h"


// Window dimensions
const unsigned width = 1280;
const unsigned int height = 720;
GLFWwindow* window;
// Used to Lock/Unlock the camera using the TAB key
bool camLocked = true;
// Change the type of light in the shader
// 0 = Directional
// 1 = Spot
// 2 = Point
int light_type = 1;

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
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
		camLocked = !camLocked;
	}	
}

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
	glfwSwapInterval( 0 );
	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW." << std::endl;
		return true;
	}

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////		Test for Skybox		/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float skybox_vertices[] =
{
	//Skybox coordinates
	-1.0, -1.0, 1.0,//
	 1.0, -1.0, 1.0,//
	 1.0, -1.0, -1.0,//
	-1.0, -1.0, -1.0,//
	-1.0, 1.0, 1.0,//
	 1.0, 1.0, 1.0,//
	 1.0, 1.0, -1.0,//
	-1.0, 1.0, -1.0,//
};

unsigned int skybox_indices[] =
{
	//Right
	1,2,6,
	6,5,1,
	//Left
	0,4,7,
	7,3,0,
	//Top
	4,5,6,
	6,7,4,
	//Bottom
	0,3,2,
	2,1,0,
	//Back
	0,1,5,
	5,4,0,
	//Front
	3,7,6,
	6,2,3
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////		Test for Skybox		/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	if (InitWindow()) // If the window was not created
		return -1;

	Shader default_shader = Shader("Shaders/default.vert", "Shaders/default.frag");
	
	// Take care of all the light related things.
	// You can change the type of light in the shader
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 10.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	default_shader.Activate();
	glUniform4f(glGetUniformLocation(default_shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(default_shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform1i(glGetUniformLocation(default_shader.ID, "lightingType"), light_type);
	

	Shader skybox_Shader = Shader("Shaders/Skybox.vert", "Shaders/Skybox.frag");
	Board board(64);
	
	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Camera
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 80.0f));

#pragma region PIECE PROPERTIES
	PawnProps pawn_props =
		{
		5.0f,
		0.0f,
		2.0f,
		1.5f,
		16,
		16
		};
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
	QueenProps queen_props =
	{
		2.8f,
		2.5f,
		1.8f,
		12.0f,
		1.5f,
		2.0f,
		2.5f,
		3.0f,
		16,
		16
	};
#pragma endregion
	
	// Create a vector of 8 pawns
	std::vector<Pawn> white_pawns;
	std::vector<Pawn> black_pawns;

	// Create the pawns and set their position using MATHHH
	for (size_t i = 0; i < 8; i++)
	{
		white_pawns.emplace_back(pawn_props, true);
		white_pawns[i].setScale(glm::vec3(0.6f, 0.6f, 0.6f));
		white_pawns[i].setPosition(glm::vec3(-4.5f + (1.28f * i), 1.3f, 1.95f));

		black_pawns.emplace_back(pawn_props, false);
		black_pawns[i].setScale(glm::vec3(0.6f, 0.6f, 0.6f));
		black_pawns[i].setPosition(glm::vec3(-4.5f + (1.28f * i), 1.3f, -4.4f));
	}

#pragma region PIECE CREATION
	Rook rookWhiteOne(rook_props, true);
	rookWhiteOne.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	rookWhiteOne.setPosition(glm::vec3(-4.7f, .8f, 3.3f));

	Rook rookWhiteTwo(rook_props, true);
	rookWhiteTwo.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	rookWhiteTwo.setPosition(glm::vec3(4.7f, .8f, 3.3f));

	Rook rookBlackOne(rook_props, false);
	rookBlackOne.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	rookBlackOne.setPosition(glm::vec3(-4.7f, .8f, -6.0f));

	Rook rookBlackTwo(rook_props, false);
	rookBlackTwo.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	rookBlackTwo.setPosition(glm::vec3(4.7f, .8f, -6.0f));
	
	Bishop bishopBlackOne(bishop_props, false);
	bishopBlackOne.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	bishopBlackOne.setPosition(glm::vec3(-2.0f, .8f, -6.0f));
	
	Bishop bishopBlackTwo(bishop_props, false);
	bishopBlackTwo.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	bishopBlackTwo.setPosition(glm::vec3(2.0f, .8f, -6.0f));

	Bishop bishopWhiteOne(bishop_props, true);
	bishopWhiteOne.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	bishopWhiteOne.setPosition(glm::vec3(-2.0f, .8f, 3.3f));

	Bishop bishopWhiteTwo(bishop_props, true);
	bishopWhiteTwo.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	bishopWhiteTwo.setPosition(glm::vec3(2.0f, .8f, 3.3f));
	
	Knight knightBlackOne(knight_props, false);
	knightBlackOne.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	knightBlackOne.setPosition(glm::vec3(-3.35f, .8f, -6.0f));

	Knight knightBlackTwo(knight_props, false);
	knightBlackTwo.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	knightBlackTwo.setPosition(glm::vec3(3.35f, .8f, -6.0f));

	Knight knightWhiteOne(knight_props, true);
	knightWhiteOne.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	knightWhiteOne.setPosition(glm::vec3(-3.35f, .8f, 3.3f));

	Knight knightWhiteTwo(knight_props, true);
	knightWhiteTwo.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	knightWhiteTwo.setPosition(glm::vec3(3.35f, .8f, 3.3f));
	
	King kingBlack(king_props, false);
	kingBlack.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	kingBlack.setPosition(glm::vec3(-0.65f, .8f, -6.0f));

	King kingWhite(king_props, true);
	kingWhite.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	kingWhite.setPosition(glm::vec3(-0.65f, .8f, 3.3f));
	
	Queen queenBlack(queen_props, false);
	queenBlack.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	queenBlack.setPosition(glm::vec3(0.65f, .8f, -6.0f));
	
	Queen queenWhite(queen_props, true);
	queenWhite.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	queenWhite.setPosition(glm::vec3(0.65f, .8f, 3.3f));
#pragma endregion
	
	Terrain terrain("Textures/terrain.png");
	terrain.transform.setLocalScale(glm::vec3(0.5f, 0.5f, 0.5f));
	terrain.transform.setLocalPosition(glm::vec3(0.0f, -6.0f, 0.0f));

	IMGUI_CHECKVERSION();
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();
		

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////		Test for Skybox		/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_vertices), &skybox_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skybox_indices), &skybox_indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	std::string facesCubeMap[6] =
	{
		"Textures/SkyRight.png",
		"Textures/SkyLeft.png",
		"Textures/SkyTop.png",
		"Textures/SkyBottom.png",
		"Textures/SkyFront.png",
		"Textures/SkyBack.png"
	};

	unsigned int cubemapTexture;
	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// These are very important to prevent seams
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// Cycles through all the textures and attaches them to the cubemap object
	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(facesCubeMap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture: " << facesCubeMap[i] << std::endl;
			stbi_image_free(data);
		}
	}

	skybox_Shader.Activate();
	glUniform1i(glGetUniformLocation(skybox_Shader.ID, "skybox"), 0);
	

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////		Test for Skybox		/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	while (!glfwWindowShouldClose(window))
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Ensure ImGui::Begin is called at least once during initialization
		bool showFpsWindow = true;  // Toggle this flag based on your requirements

		if (showFpsWindow && ImGui::Begin("FPS Counter", &showFpsWindow,
		                                  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
		                                  ImGuiWindowFlags_NoCollapse))
		{
			ImGui::SetWindowPos(ImVec2(5, 5));  // Set the desired screen coordinates
			ImGui::SetNextWindowSize(ImVec2(150, 100));  // Set the desired window size
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			
			ImGui::End();
		}
		//ImGui::ShowDemoWindow(); // Show demo window! :)
		// Input
		processInput(window);
		// ******************************* Rendering commands here ******************************************************
		// Clear the screen to a specific color

		//Clear color to black (not really necessary actually since we are drawing a background image)
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Also clear the depth buffer now!
		
		
		camera.updateMatrix(20.0f, 0.1f, 200.0f);
		camera.Inputs(window, camLocked);
		
		// For loop to render all the Pawn objects
		 board.Draw(default_shader, camera);
		 for (auto pawn : white_pawns)
		 {
		 	pawn.Render(default_shader, camera);
		 }
		 for (auto pawn : black_pawns)
		 {
		 	pawn.Render(default_shader, camera);
		 }


		
#pragma region RENDERING
		 //Render rooks
		 rookWhiteOne.Render(default_shader, camera);
		rookWhiteTwo.Render(default_shader, camera);
		rookBlackOne.Render(default_shader, camera);
		rookBlackTwo.Render(default_shader, camera);
		
		//Render knights
		knightWhiteOne.Render(default_shader, camera);
		knightWhiteTwo.Render(default_shader, camera);
		knightBlackOne.Render(default_shader, camera);
		knightBlackTwo.Render(default_shader, camera);
		
		//Render bishops
		bishopBlackOne.Render(default_shader, camera);
		bishopBlackTwo.Render(default_shader, camera);
		bishopWhiteOne.Render(default_shader, camera);
		bishopWhiteTwo.Render(default_shader, camera);
		
		//Render kings
		kingBlack.Render(default_shader, camera);
		kingWhite.Render(default_shader, camera);
		
		//Render queens
		queenBlack.Render(default_shader, camera);
		queenWhite.Render(default_shader, camera);
		
		//Render terrain
		terrain.Render(default_shader, camera);
#pragma endregion

		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////		Test for Skybox		/////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		glDepthFunc(GL_LEQUAL);
		skybox_Shader.Activate();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		glUniformMatrix4fv(glGetUniformLocation(skybox_Shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skybox_Shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// Draws the cubemap as the last object so we can save a bit of performance by discarding all fragments
		// where an object is present (a depth of 1.0f will always fail against any object's depth value)
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Switch back to the normal depth function
		glDepthFunc(GL_LESS);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////		Test for Skybox		/////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// (Your code clears your framebuffer, renders your other stuff etc.)
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	default_shader.Delete();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	//ImGui::End();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;



}

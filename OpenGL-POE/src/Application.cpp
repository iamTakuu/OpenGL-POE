#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stb/stb_image.h>
#include <vector>

#include "../Headers/Shader.h"
#include "../Headers/VBO.h"
#include "../Headers/VAO.h"
#include "../Headers/IBO.h"
#include "../Headers/Texture.h"
#include "../Headers/Camera.h"

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
const unsigned width = 480;
const unsigned int height = 480;
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

std::vector<GLfloat> terrain_vertices;
std::vector<GLuint> terrain_indices;

// Function to load a heightmap image
bool loadHeightmap(const char* filename, std::vector<unsigned char>& heightmap, int& width, int& height) {
	// Load the image using your preferred image loading library
	// For simplicity, let's assume you have a function for this
	// For example, using stb_image.h:
	int channels;
	unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
	if (!image) {
		std::cerr << "Failed to load heightmap." << std::endl;
		return false;
	}

	// Convert the image to grayscale and store it in the heightmap vector
	heightmap.resize(width * height);
	for (int i = 0; i < width * height; i++) {
		// Convert RGB to grayscale by averaging channels
		heightmap[i] = (image[i * channels] + image[i * channels + 1] + image[i * channels + 2]) / 3;
	}

	stbi_image_free(image);
	return true;
}

 


// Function to generate the terrain mesh from the heightmap
void generateTerrainMesh(const std::vector<unsigned char>& heightmap, int width, int height, int numstrips, int numtrisPerStrip) {
	// Calculate the vertex positions and store them in the 'vertices' vector
	float yScale = 64.0f / 256.0f, yShift = 16.0f;
	int rez = 1;
	
	for (int z = 0; z < height; z++) {
		for (int x = 0; x < width; x++) {
			float xPos = static_cast<float>(x);
			float zPos = static_cast<float>(z);
			float yPos = static_cast<float>(heightmap[z * width + x]) / 10.0f; // Scale the height

			terrain_vertices.push_back(xPos);
			terrain_vertices.push_back(yPos);
			terrain_vertices.push_back(zPos);
		}
	}

	std::cout << "Loaded " << terrain_vertices.size() / 3 << " vertices" << std::endl;
	

	// Calculate the indices for rendering the terrain
	for (unsigned i = 0; i < height - 1; i += rez)
	{
		for (unsigned j = 0; j < width; j += rez)
		{
			for (unsigned k = 0; k < 2; k++)
			{
				terrain_indices.push_back(j + width * (i + k * rez));
			}
		}
	}
	std::cout << "Loaded " << terrain_indices.size() << " indices" << std::endl;

	numstrips = (height - 1) / rez;
	numtrisPerStrip == (width / rez) * 2 - 2;
	std::cout << "Created lattice of " << numstrips << " strips with " << numtrisPerStrip << " triangles each" << std::endl;
	std::cout << "Created " << numstrips * numtrisPerStrip << " triangles total" << std::endl;
}


int main()
{
	const int numStrips = 0;
	const int numTrisPerStrip = 0;

	if (InitWindow()) // If the window was not created
		return -1;
	// Camera
	Camera camera(width, height, glm::vec3(0.0f, 0.5f, 3.0f));
	
	glEnable(GL_DEPTH_TEST);

	// Create the shader program
	Shader shaderProgram = Shader("Shaders/default.vert", "Shaders/default.frag");
		
	// Load the heightmap and generate the terrain mesh
		std::vector<unsigned char> heightmap;
		int heightmapWidth, heightmapHeight;
		if (!loadHeightmap("Height Map/Terrain.png", heightmap, heightmapWidth, heightmapHeight)) {
			glfwTerminate();
			return -1;
		}
		generateTerrainMesh(heightmap, heightmapWidth, heightmapHeight, numStrips, numTrisPerStrip);

		// first, configure the cube's VAO (and terrainVBO + terrainIBO)
		unsigned int terrainVAO, terrainVBO, terrainIBO;
		glGenVertexArrays(1, &terrainVAO);
		glBindVertexArray(terrainVAO);

		glGenBuffers(1, &terrainVBO);
		glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
		glBufferData(GL_ARRAY_BUFFER, terrain_vertices.size() * sizeof(float), &terrain_vertices[0], GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &terrainIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, terrain_indices.size() * sizeof(unsigned), &terrain_indices[0], GL_STATIC_DRAW);


	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// Rendering commands here
		// Clear the screen to a specific color
		glClearColor(0.09f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Also clear the depth buffer now!

		shaderProgram.Activate();
		camera.Input(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
		
		glBindVertexArray(terrainVAO);
		//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		for (unsigned strip = 0; strip < numStrips; strip++)
		{
			glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
				numTrisPerStrip + 2,   // number of indices to render
				GL_UNSIGNED_INT,     // index data type
				(void*)(sizeof(unsigned) * (numTrisPerStrip + 2) * strip)); // offset to starting index
		}

		// Check events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	

	glfwTerminate();
	return 0;



}

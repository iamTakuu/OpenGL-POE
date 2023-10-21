#include "../Headers/Board.h"

const Vertex tileVertex[] =
{
	//              COORDINATES           /            COLORS          /      TEXTURE COORDINATES    //
	Vertex{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, //Front
	Vertex{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, //Back
	Vertex{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},//Back
	Vertex{glm::vec3(1.0f, -1.0f,  1.0f),  glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},//Front

	Vertex{glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, //Front
	Vertex{glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},//Back
	Vertex{glm::vec3(1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},//Back
	Vertex{glm::vec3(1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)}  //Front
};

const Vertex boarderVertices[] =
{
	//              COORDINATES           /            COLORS          /      TEXTURE COORDINATES    //
	Vertex{glm::vec3(-9.0f, -9.0f,  0.5f), glm::vec3(2.0f, 0.5f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-9.0f, -9.0f, -0.5f), glm::vec3(2.0f, 0.5f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(9.0f, -9.0f, -0.5f), glm::vec3(2.0f, 0.5f, 1.0f), glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(9.0f, -9.0f,  0.5f),  glm::vec3(2.0f, 0.5f, 1.0f), glm::vec2(1.0f, 0.0f)},

	Vertex{glm::vec3(-9.0f,  9.0f,  0.5f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(-9.0f,  9.0f, -0.5f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(9.0f,  9.0f, -0.5f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(9.0f,  9.0f,  0.5f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)}
};

const GLuint cubeIndices[] =
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

Board::Board(GLuint count, Shader& shaderProgram)
{
	// Texture textures[] =
	// {
	// 	// Leave textType blank for now, later we will use it to determine the type of texture.
	// 	// Like diffuse, specular, etc.
	// 	//Texture("Textures/pop_cat.png", "", 0, GL_RGBA, GL_UNSIGNED_BYTE),
	// 	Texture("Textures/white.png", "", 0, GL_RGB, GL_UNSIGNED_BYTE), // Text Index: 0
	// 	Texture("Textures/black.png", "", 0, GL_RGB, GL_UNSIGNED_BYTE) // Text Index: 1
	// };

	Texture whiteTexture = Texture("Textures/white.png", "", 0, GL_RGB, GL_UNSIGNED_BYTE);
	Texture blackTexture = Texture("Textures/black.png", "", 0, GL_RGB, GL_UNSIGNED_BYTE);
	// Create the shader program
	//Shader shaderProgram = Shader("Shaders/default.vert", "Shaders/default.frag");

	std::vector <Vertex> tileVerts(tileVertex, tileVertex + sizeof(tileVertex) / sizeof(Vertex));
	//std::vector <Vertex> blackVerts(blackVertices, blackVertices + sizeof(blackVertices) / sizeof(Vertex));

	std::vector <Vertex> boarderVerts(boarderVertices, boarderVertices + sizeof(boarderVertices) / sizeof(Vertex));

	std::vector <GLuint> ind(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
	//std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	glm::vec3 pos = glm::vec3(-4.5f, -4.5f, 0.0f);
	bool startWhite = false;
	for (size_t i = 0; i < count; i++)
	{

		if (startWhite)
		{
			// Add the white mesh to the vector
			m_meshes.push_back((i % 2 == 0) ? Mesh(tileVerts, ind, whiteTexture) : Mesh(tileVerts, ind, blackTexture));
		}
		else
		{
			// Add the black mesh to the vector
			m_meshes.push_back((i % 2 == 0) ? Mesh(tileVerts, ind, blackTexture) : Mesh(tileVerts, ind, whiteTexture));
		}
		
		
		// Add the position and model matrix to the vectors
		m_positions.push_back(pos);
		m_models.push_back(glm::mat4(1.0f));
		// Translate the model matrix to the position of the cube
		m_models[i] = glm::translate(m_models[i], m_positions[i]);

		// Move the position of the next cube
		pos.x += 1.0f;
		// Randomly offset the z position between 0.0 and 0.2
		pos.z = (float)rand() / RAND_MAX * 0.2f;


		// If we have reached the end of the row, move to the next row
		if ((i + 1) % 8 == 0)
		{
			pos.x = -4.5f;
			pos.y += 1.0f;
			startWhite = !startWhite;
		}
	}
	
	// Add the boarder mesh to the vector
	m_meshes.push_back(Mesh(boarderVerts, ind, whiteTexture));
	m_positions.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	m_models.push_back(glm::mat4(1.0f));
	m_models[count] = glm::translate(m_models[count], m_positions[count]);
}



void Board::Draw(Shader& shaderProgram, Camera& camera)
{
	for (size_t i = 0; i < m_meshes.size(); i++)
	{
		shaderProgram.Activate();
		// Set the model matrix
		shaderProgram.setMat4("model", parent_model * m_models[i]);

		m_meshes[i].Draw(shaderProgram, camera);
	}
}
#include "../Headers/Board.h"

Board::Board(GLuint count)
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
	Texture boarderTexture = Texture("Textures/boarder.png", "", 0, GL_RGB, GL_UNSIGNED_BYTE);
	// Create the shader program
	//Shader shaderProgram = Shader("Shaders/default.vert", "Shaders/default.frag");

	//std::vector <Vertex> tileVerts(tileVertex, tileVertex + sizeof(tileVertex) / sizeof(Vertex));
	//std::vector <Vertex> blackVerts(blackVertices, blackVertices + sizeof(blackVertices) / sizeof(Vertex));

	//std::vector <Vertex> boarderVerts(boarderVertices, boarderVertices + sizeof(boarderVertices) / sizeof(Vertex));

	//std::vector <GLuint> ind(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
	//std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	// Rotate the board 90 degrees
	//m_transform.setLocalRotation(glm::vec3(90.0f, 0.0f, 0.0f));
	m_transform.setLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	//m_transform.setLocalScale(glm::vec3(0.5f, 0.5f, 0.5f));
	
	glm::vec3 pos = glm::vec3(-4.5f, 0.0f, -4.5f);
	bool startWhite = false;
	for (size_t i = 0; i < count; i++)
	{

		if (startWhite)
		{
			//m_cubes.push_back(Cube(whiteTexture).transform.setParent(m_transform));
			// Add the white mesh to the vector
			m_cubes.push_back((i % 2 == 0) ? Cube(whiteTexture) :  Cube(blackTexture));
			
		}
		else
		{
			// Add the black mesh to the vector
			m_cubes.push_back((i % 2 == 0) ? Cube(blackTexture) :  Cube(whiteTexture));
			//m_meshes.push_back((i % 2 == 0) ? Mesh(tileVerts, ind, blackTexture) : Mesh(tileVerts, ind, whiteTexture));
		}
		
		
		// Add the position and model matrix to the vectors
		m_cubes[i].transform.setLocalPosition(
			m_cubes[i].transform.getRight()+ pos
			);
		m_cubes[i].transform.setParent(&m_transform);
		m_cubes[i].transform.computeModelMatrix();
		//m_positions.push_back(pos);
		//m_models.push_back(glm::mat4(1.0f));
		// Translate the model matrix to the position of the cube
		//m_models[i] = glm::translate(m_models[i], m_positions[i]);

		// Move the position of the next cube
		pos.x += 1.0f;
		// Randomly offset the z position between 0.0 and 0.2
		pos.y = (float)rand() / RAND_MAX * 0.2f;


		// If we have reached the end of the row, move to the next row
		if ((i + 1) % 8 == 0)
		{
			pos.x = -4.5f;
			pos.z += 1.0f;
			startWhite = !startWhite;
		}
	}

	// Compute model matrix for all the cubes
	// for (auto cube : m_cubes)
	// {
	// 	cube.transform.computeModelMatrix();
	// }
	
	m_cubes.push_back(Cube(boarderTexture));
	m_cubes[count].transform.setLocalPosition(glm::vec3(.0f, 0.0f, -.5f));
	m_cubes[count].transform.setLocalScale(glm::vec3(3.0f, .7f, 3.0f));
	// Add the boarder mesh to the vector
	//m_meshes.push_back(Mesh(boarderVerts, ind, whiteTexture));
	//m_positions.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	//m_models.push_back(glm::mat4(1.0f));
	//m_models[count] = glm::translate(m_models[count], m_positions[count]);
}



void Board::Draw(Shader& shaderProgram, Camera& camera)
{
	for (size_t i = 0; i < m_cubes.size(); i++)
	{
		// Set the model matrix
		shaderProgram.Activate();
		shaderProgram.setMat4("model", m_transform.getModelMatrix());
		m_cubes[i].Render(shaderProgram, camera);
	}
}
#include "../Headers/Board.h"

Board::Board(GLuint count)
{

	Texture whiteTexture = Texture("Textures/white.png", "", 0, GL_RGB, GL_UNSIGNED_BYTE);
	Texture blackTexture = Texture("Textures/black.png", "", 0, GL_RGB, GL_UNSIGNED_BYTE);
	Texture boarderTexture = Texture("Textures/boarder.png", "", 0, GL_RGB, GL_UNSIGNED_BYTE);
	
	m_transform.setLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	
	glm::vec3 pos = glm::vec3(-4.5f, 0.0f, -4.5f);
	bool startWhite = false;
	for (size_t i = 0; i < count; i++)
	{

		if (startWhite)
		{
			m_cubes.push_back((i % 2 == 0) ? Cube(whiteTexture) :  Cube(blackTexture));
		}
		else
		{
			m_cubes.push_back((i % 2 == 0) ? Cube(blackTexture) :  Cube(whiteTexture));
		}
		
		
		// Add the position and model matrix to the vectors
		m_cubes[i].transform.setLocalPosition(
			m_cubes[i].transform.getRight()+ pos
			);
		m_cubes[i].transform.setParent(&m_transform);
		m_cubes[i].transform.computeModelMatrix();

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
	
	m_cubes.push_back(Cube(boarderTexture));
	m_cubes[count].transform.setLocalPosition(glm::vec3(.0f, 0.0f, -.5f));
	m_cubes[count].transform.setLocalScale(glm::vec3(3.0f, .7f, 3.0f));
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
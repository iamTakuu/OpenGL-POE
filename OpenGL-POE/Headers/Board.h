#pragma once
#include <GL/glew.h>
#include <queue>

#include "Shader.h"
#include "Mesh.h"


class Board
{
	public:

		Board(GLuint count, Shader& shaderProgram);
		void Draw(Shader& shader, Camera& camera);


	private:
		//void DrawBoarder();
		std::vector<Mesh> m_meshes;
		std::vector<glm::vec3> m_positions;
		std::vector<glm::mat4> m_models = { glm::mat4(1.0f)};
	
};

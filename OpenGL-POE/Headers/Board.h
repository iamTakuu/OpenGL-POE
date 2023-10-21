#pragma once
#include <GL/glew.h>

#include "Cube.h"
#include "Shader.h"
#include "Mesh.h"
#include "Transform.h"


class Board
{
	public:

		Transform m_transform;
		Board(GLuint count);
		void Draw(Shader& shader, Camera& camera);
		//glm::mat4 parent_model = { glm::mat4(1.0f) };


	private:
		//void DrawBoarder();
		std::vector<Cube> m_cubes;
		//std::vector<Mesh> m_meshes;
		//std::vector<glm::vec3> m_positions;
		//std::vector<glm::mat4> m_models = { glm::mat4(1.0f)};
	
};

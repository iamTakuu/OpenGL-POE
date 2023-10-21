#pragma once
#include <GL/glew.h>
#include "Mesh.h"
#include "Transform.h"

class Sphere
{
public:
	Sphere(GLfloat radius = 1.0f, GLint sectorCount = 36, GLint stackCount = 1);

	void Render(Shader& shader, Camera& camera);
	Transform transform;
	
private:
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;
	

	Mesh m_mesh;
	GLint sectorCount;
	GLint stackCount;
	GLfloat radius;

	void setVertices();
	void setIndices();
	void SetupMesh();

	


};


#pragma once
#include <GL/glew.h>
#include "Mesh.h"
#include "Transform.h"

class Sphere
{
public:
	Sphere(GLfloat radius = 1.0f, GLint sectorCount = 36, GLint stackCount = 1, const Texture& texture = Texture());

	void Render(Shader& shader, Camera& camera);
	Transform transform;
	
private:
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;
	

	Mesh m_mesh;
	GLint sectorCount;
	GLint stackCount;
	GLfloat radius;

	Texture m_texture;

	void setVertices();
	void setIndices();
	void calculateNormals();
	void SetupMesh();

	


};


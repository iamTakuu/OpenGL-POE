#pragma once
#include <vector>
#include <GL/glew.h>
#include "Mesh.h" 
#include "Transform.h"


class Terrain
{
public:
	Terrain(const char* heightMap);
	void Render(Shader& shader, Camera& camera);

	Transform transform;

private:
	
	Mesh m_mesh;
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;

	Texture m_texture;

	unsigned char* m_data;
	int m_width, m_height, m_nrChannels;
	
	void setVertices();
	void setIndices();
	void SetupMesh();
	
};

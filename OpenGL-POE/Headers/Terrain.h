#pragma once
#include <iostream>
#include <stb/stb_image.h>
#include <vector>
#include <GL/glew.h>
#include "Mesh.h" 


class Terrain
{
public:
	Terrain(const char* img);
	void Draw(Shader& shader, Camera& camera);
	// Mesh generation
	std::vector<GLfloat> terrain_vertices;
	std::vector<GLuint> terrain_indices;

	private:
		glm::mat4 model = glm::mat4(1.0f);
		unsigned int terrainVAO, terrainVBO, terrainIBO;
		int numStrips = 0;
		int numTrisPerStrip = 0;


	//std::vector<Vertex.Position> positions;
	
	//std::vector<unsigned char>& heightMap;

	//int nrChannels;
};
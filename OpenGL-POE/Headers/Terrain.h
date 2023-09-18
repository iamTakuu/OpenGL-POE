#pragma once
#include <iostream>
#include <stb/stb_image.h>
#include <vector>
#include <GL/glew.h>


class Terrain
{
public:
	Terrain(const char* img);

	// Mesh generation
	std::vector<GLfloat> terrain_vertices;
	std::vector<GLuint> terrain_indices;

	//std::vector<unsigned char>& heightMap;

	//int nrChannels;
};
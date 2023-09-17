#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>

#include "VAO.h"
#include "IBO.h"
#include "Camera.h"
#include "Texture.h"

// Wrapper class for a mesh generation.
class Mesh
{
	public:
		std::vector <Vertex> vertices; // Uses vector instead of array because we don't know how many vertices we will have
		std::vector <GLuint> indices;
		std::vector <Texture> textures;

		VAO VAO;

		// Constructor that loads the mesh's vertices, indices, and textures
		Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

		// Draws the mesh
		void Draw(Shader& shader, Camera& camera);

	private:
		void SetupMesh();

};


#endif // !MESH_CLASS_H

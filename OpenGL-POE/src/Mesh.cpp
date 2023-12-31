#include "../Headers/Mesh.h"


Mesh::Mesh()
{
}

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, Texture& texture)
{
	this->vertices = vertices;
	this->indices = indices;
	this->texture = texture;
	
	// Now that we have all the required data, set the vertex buffers and its attribute pointers.
	SetupMesh();
}

void Mesh::SetupMesh()
{
	VAO.Bind();
	// Create the VBO and link to vertices
	VBO VBO(vertices);
	// Create the IBO and link to indices
	IBO IBO(indices);
	// Takes in the layout, how many components per attrib (as in 3 for vert and col )
	// type of components,
	// stride, and offset
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0); // Vertex attributes
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float))); // Color attributes
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float))); // Texture coord attributes
	VAO.LinkAttrib(VBO, 3, 3, GL_FLOAT, sizeof(Vertex), (void*)(8 * sizeof(float))); // Normal attributes
	VAO.Unbind();
	VBO.Unbind();
	IBO.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
	shader.Activate();
	VAO.Bind();
	// Bind appropriate textures
	texture.texUnit(shader, "tex0", 0);
	texture.Bind();

	//Camera
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");
	
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::isTerrain(int width, int height, int resolution)
{
	m_isTerrain = true;
	numStrips = (height - 1) / resolution;
	numTrisPerStrip = (width/resolution) * 2 - 2;
}


#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

struct Vertex
{
	// Position
	glm::vec3 Position;
	// Color
	glm::vec3 Color;
	// Normal ... we'll get to this later.
	//glm::vec3 Normal;
	// TexCoords
	glm::vec2 TexCoords;
};

// Vertex Buffer Object
// Stores large number of vertices in the GPU's memory
// Allows us to send large batches of data all at once to the GPU instead of sending data a vertex at a time
class VBO
{
public:
	// ID reference of the Vertex Buffer Object
	GLuint ID;
	//Generates a Vertex Buffer Object and links it to vertices
	VBO(std::vector<Vertex>& vertices);

	void Bind();
	void Unbind();
	void Delete();
};




#endif // !VBO_CLASS_H


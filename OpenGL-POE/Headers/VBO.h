#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <GL/glew.h>

// Vertex Buffer Object
// Stores large number of vertices in the GPU's memory
// Allows us to send large batches of data all at once to the GPU instead of sending data a vertex at a time
class VBO
{
public:
	GLuint ID;
	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};




#endif // !VBO_CLASS_H


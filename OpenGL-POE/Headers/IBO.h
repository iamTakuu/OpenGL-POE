#ifndef IBO_CLASS_H
#define IBO_CLASS_H

#include <GL/glew.h>

// Index (Element) Buffer Object
// Stores indices that OpenGL uses to decide what vertices to draw
// Allows us to reuse vertices
class IBO
{
public:
	GLuint ID;
	IBO(GLuint* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif // !IBO_CLASS_H


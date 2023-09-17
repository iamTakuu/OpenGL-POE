#ifndef IBO_CLASS_H
#define IBO_CLASS_H

#include <GL/glew.h>
#include <vector>

// Index (Element) Buffer Object
// Stores indices that OpenGL uses to decide what vertices to draw
// Allows us to reuse vertices
class IBO
{
public:
	GLuint ID;
	IBO(std::vector<GLuint>& indices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif // !IBO_CLASS_H


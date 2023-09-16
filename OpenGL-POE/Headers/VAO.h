#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <GL/glew.h>
#include "VBO.h"

// Vertex Array Object
// Links vertex attributes to a vertex shader
// Allows us to use multiple VBOs at the same time
class VAO
{
	public:
		GLuint ID;
		VAO();

		void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();
};
#endif // !VAO_CLASS_H


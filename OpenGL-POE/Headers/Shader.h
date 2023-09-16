#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>


std::string get_file_contents(const char* filename);
// Shader class
// Compiles and generates a shader program
// Usage:
// Shader shader("path/s.vert", "path/s.frag");
class Shader
{
	public:
		GLuint ID;
		Shader(const char* vertexPath, const char* fragmentPath);
		Shader(const char* vertexCode, const char* fragmentCode, bool notFile);

		void Activate();
		void Disgard();
		void Delete();
		void setMat4(const std::string& name, const glm::mat4& mat) const
		{
			glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
};

#endif
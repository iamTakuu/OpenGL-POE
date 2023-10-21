#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <glm/fwd.hpp>


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
		
		// Activate the shader by calling glUseProgram
		void Activate();
		void setMat4(const GLchar* name, const glm::mat4& mat) const;
		void Disgard();
		void Delete();
		// Utility function to check for shader compile errors
		void compileErrors(unsigned int shader, const char* type);

};

#endif
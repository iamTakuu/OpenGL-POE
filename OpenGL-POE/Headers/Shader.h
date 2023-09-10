#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <GL/glew.h>
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

};

#endif
#include "../Headers/Shader.h"

#include <glm/gtc/type_ptr.hpp>

/*Coder, I. (2011). Insane Coding: How to read in a file in C++. [online] Insane Coding.
Available at: https://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html 
[Accessed 10 Sep. 2023].
‌*/

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize((unsigned int)in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// For when you want to read from a file
// and pass in the file path
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;

	try
	{
		vertexCode = get_file_contents(vertexPath);
		fragmentCode = get_file_contents(fragmentPath);
	}
	catch (const std::exception&)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();


	// Create the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	compileErrors(vertexShader, "VERTEX");

	// Create the shader program and link the shaders to it
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wrap/Link up shaders into a program
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");
	//glUseProgram(ID);

	// Delete the shaders as the program has them now
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// For when you want to pass in the shader code as a string
// instead of reading from a file
Shader::Shader(const char* vertexCode, const char* fragmentCode, bool notFile)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	glCompileShader(fragmentShader);

	// Create the shader program and link the shaders to it
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wrap/Link up shaders into a program
	glLinkProgram(ID);
	//glUseProgram(ID);

	// Delete the shaders as the program has them now
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


void Shader::Activate()
{
	glUseProgram(ID);
}
void Shader::Disgard()
{
	glDeleteProgram(ID);
}
void Shader::setMat4(const GLchar* name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(mat));
}


void Shader::Delete()
{
	glDeleteProgram(ID);
}
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	// Check if the shader was compiled successfully
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << std::endl << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "PROGRAM_LINKING_ERROR for: " << type << std::endl << infoLog << std::endl;
		}
	}
}
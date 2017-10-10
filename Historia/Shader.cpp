#include "Shader.h"
#include <fstream>
#include <sstream>
#include <string>

Shader::Shader()
{
	_program = glCreateProgram();
}

Shader::~Shader()
{
	glDeleteProgram(_program);
}

// Attach and delete all created shaders and link the program
void Shader::LinkShaders()
{
	glLinkProgram(_program);
}

bool Shader::CompileShader(const char* shaderPath, GLenum shaderType)
{
	bool success = true;

	std::string shaderTypeString;
	// retrieve the shader source code from the filepath
	std::string shaderCode;
	std::ifstream shaderFile;

	// Ensure ifstream object can throw exceptions
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		printf("Error: Shader not successfully read\n");
		success = false;
	}

	const GLchar* codeResults = shaderCode.c_str();
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &codeResults, NULL);
	glCompileShader(shader);

	// Determine which shader needs to be reassigned
	switch (shaderType)
	{
	case GL_VERTEX_SHADER:
		_vertexShader = shader;
		break;
	case GL_FRAGMENT_SHADER:
		_fragmentShader = shader;
		break;
	case GL_TESS_CONTROL_SHADER:
		_tessControlShader = shader;
		break;
	case GL_TESS_EVALUATION_SHADER:
		_tessEvaluationShader = shader;
		break;
	case GL_GEOMETRY_SHADER:
		_geometryShader = shader;
		break;
	default:
		success = false;
		printf("Shader not created: Unknown shader type\n");
		break;
	}

	char infoLog[512];
	int shaderSuccess;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderSuccess);

	if (!shaderSuccess)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("Error: shader compilation failed: %s\n", infoLog);
	}

	glAttachShader(_program, shader);
	glDeleteShader(shader);

	return success;
}

GLuint Shader::VertexShader()
{
	return _vertexShader;
}

GLuint Shader::FragmentShader()
{
	return _fragmentShader;
}

GLuint Shader::Program()
{
	return _program;
}

void Shader::setVec2(const char* name, glm::vec2 vec)
{
	glUniform2f(glGetUniformLocation(_program, name), vec.x, vec.y);
}

void Shader::setVec3(const char* name, glm::vec3 vec)
{
	glUniform3f(glGetUniformLocation(_program, name), vec.x, vec.y, vec.z);
}

void Shader::setMat4(const char* name, glm::mat4 &mat)
{
	glUniformMatrix4fv(glGetUniformLocation(_program, name), 1, GL_FALSE, &mat[0][0]);
}
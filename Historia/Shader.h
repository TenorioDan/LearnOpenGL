#pragma once

#include "GL_Helpers.h"

class Shader
{
public:
	Shader();
	~Shader();
	bool CompileShader(const char* shaderPath, GLenum shaderType);
	GLuint VertexShader();
	GLuint FragmentShader();
	GLuint Program();

	void LinkShaders();

private:
	GLuint _vertexShader;
	GLuint _tessControlShader;
	GLuint _tessEvaluationShader;
	GLuint _geometryShader;
	GLuint _fragmentShader;
	GLuint _program;

};
#pragma once

#include "GL_Helpers.h"
#include <glm/glm.hpp>

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

	void setVec2(const char* name, glm::vec2 vec);
	void setVec3(const char* name, glm::vec3 vec);
	void setMat4(const char* name, glm::mat4 &mat);

private:
	GLuint _vertexShader;
	GLuint _tessControlShader;
	GLuint _tessEvaluationShader;
	GLuint _geometryShader;
	GLuint _fragmentShader;
	GLuint _program;

};
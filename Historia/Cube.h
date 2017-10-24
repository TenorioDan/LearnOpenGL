#pragma once

#include "GameObject.h"

class Cube : public GameObject
{
public:
	static void init();

	void update(float currentTime);
	void render(glm::mat4 VPMatrix, Shader& lightShader);
	void translate(GLfloat x, GLfloat y, GLfloat z);

private:
	static GLuint _vbo;
	static GLuint _vao;
	static Shader* _lightShader;
	
	// lighting textures
	static GLuint _diffuseMap, _specularMap;

	glm::vec3 _position = glm::vec3();
	glm::vec3 _color = glm::vec3(0.64f, 0.64f, 0.64f);
	//glm::vec3 _color = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::mat4 _model = glm::mat4();
	
};
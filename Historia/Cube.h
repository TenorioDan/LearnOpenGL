#pragma once

#include "GameObject.h"

class Cube : public GameObject
{
public:
	static void init();

	void update(float currentTime);
	void render(glm::mat4 VPMatrix, glm::vec3 viewPos, glm::vec3 lightPos, glm::vec3 lightColor);
	void translate(GLfloat x, GLfloat y, GLfloat z);

private:
	static GLuint _vbo;
	static GLuint _vao;
	static Shader* _lightShader;

	glm::vec3 _position = glm::vec3();
	//glm::vec3 _color = glm::vec3(0.2f, 0.2f, 0.2f);
	glm::vec3 _color = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::mat4 _model = glm::mat4();
	
};
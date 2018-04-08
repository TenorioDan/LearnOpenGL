#pragma once

#include "GameObject.h"

class Cube : public GameObject
{
public:
	static void init();

	Cube();

	void update(float currentTime);
	void render(glm::mat4 VPMatrix, Shader& lightShader);
	void translate(GLfloat x, GLfloat y, GLfloat z);
	void translate(glm::vec3 transalation);
	void setPosition(glm::vec3 position);
	void addTexture(const char* diffusePath, const char* specularPath, const char* emissionPath);

	glm::vec3 getPosition();

private:
	static GLuint _vbo;
	static GLuint _vao;
	static Shader* _lightShader;
	
	// lighting textures
	GLuint _diffuseMap, _specularMap, _emissionMap;

	glm::vec3 _position = glm::vec3();
	glm::vec3 _color = glm::vec3(0.64f, 0.64f, 0.64f);
	//glm::vec3 _color = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::mat4 _model;
	
};
#pragma once
#include "Tutorial.h"
#include "Camera.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Learn_OpenGL_Lighting : public Tutorial
{
public:
	void init()
	{
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		stbi_set_flip_vertically_on_load(true);

		_lightShader = new Shader();
		_lightShader->CompileShader("Shaders/LearnOpenGL/Lighting/vertex_shader_1.vert", GL_VERTEX_SHADER);
		_lightShader->CompileShader("Shaders/LearnOpenGL/Lighting/light_shader.frag", GL_FRAGMENT_SHADER);
		_lightShader->LinkShaders();

		_lampShader = new Shader();
		_lampShader->CompileShader("Shaders/LearnOpenGL/Lighting/vertex_shader_1.vert", GL_VERTEX_SHADER);
		_lampShader->CompileShader("Shaders/LearnOpenGL/Lighting/lamp_shader.frag", GL_FRAGMENT_SHADER);
		_lampShader->LinkShaders();

		// vertex data containing vertex coordinates and normal values
		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		// Light shader objects
		glGenVertexArrays(1, &_lightVAO);
		glBindVertexArray(_lightVAO);

		// We only need to bind to the VBO, the container's VBO's data already contains the correct data
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		// set the vertex aettributes (only position data for the lamp)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		// Camera setup
		_projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
		_model = glm::mat4();
		_camera = new Camera();
		_camera->setCameraCommands();

		// Color setup
		_lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		_objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
		_lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
	}

	void update(double currentTime)
	{
		Tutorial::update(currentTime);
		_camera->update(currentTime);
	}

	void render(double currentTime)
	{
		Tutorial::render(currentTime);

		_model = glm::mat4();
		_view = _camera->getViewMatrix();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(_lightShader->Program());
		
		_lightPos = glm::vec3(sin(currentTime) * 2.5, 0.0f, cos(currentTime) * 2.5);

		_model = glm::rotate(_model, -(float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));

		_lightShader->setMat4("model", _model);
		_lightShader->setMat4("view", _view);
		_lightShader->setMat4("projection", _projection);
		_lightShader->setVec3("objectColor", _objectColor);
		_lightShader->setVec3("lightColor", _lightColor);
		_lightShader->setVec3("lightPos", _lightPos);
		_lightShader->setVec3("viewPos", _camera->position());

		glBindVertexArray(_vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Use the light shader object and set the uniforms
		glUseProgram(_lampShader->Program());

		_model = glm::mat4();
		_model = glm::translate(_model, _lightPos);
		_model = glm::scale(_model, glm::vec3(0.2f));

		_lampShader->setMat4("model", _model);
		_lampShader->setMat4("view", _view);
		_lampShader->setMat4("projection", _projection);

		glBindVertexArray(_lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

private:
	GLuint _vbo, _vao, _ebo, _lightVAO;
	Shader* _lightShader;
	Shader* _lampShader;
	Camera* _camera;
	glm::mat4 _model, _view, _projection;
	glm::vec3 _lightPos, _lightColor, _objectColor;
};
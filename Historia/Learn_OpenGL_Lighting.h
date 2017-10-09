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

		_shader = new Shader();
		_shader->CompileShader("Shaders/LearnOpenGL/Lighting/vertex_shader_1.vert", GL_VERTEX_SHADER);
		_shader->CompileShader("Shaders/LearnOpenGL/Lighting/fragment_shader_1.frag", GL_FRAGMENT_SHADER);
		_shader->LinkShaders();

		_lightShader = new Shader();
		_lightShader->CompileShader("Shaders/LearnOpenGL/Lighting/vertex_shader_1.vert", GL_VERTEX_SHADER);
		_lightShader->CompileShader("Shaders/LearnOpenGL/Lighting/fragment_shader_2.frag", GL_FRAGMENT_SHADER);
		_lightShader->LinkShaders();

		GLfloat vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		  	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		// Light shader objects
		glGenVertexArrays(1, &_lightVAO);
		glBindVertexArray(_lightVAO);

		// We only need to bind to the VBO, the container's VBO's data already contains the correct data
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		// set the vertex aettributes (only position data for the lamp)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
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
		glUseProgram(_shader->Program());

		GLint modelLocation = glGetUniformLocation(_shader->Program(), "model");
		GLint viewLocation = glGetUniformLocation(_shader->Program(), "view");
		GLint projectionLocation = glGetUniformLocation(_shader->Program(), "projection");

		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(_view));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(_projection));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(_model));

		glUniform3f(glGetUniformLocation(_shader->Program(), "objectColor"), _objectColor.x, _objectColor.y, _objectColor.z);
		glUniform3f(glGetUniformLocation(_shader->Program(), "lightColor"), _lightColor.x, _lightColor.y, _lightColor.z);

		glBindVertexArray(_vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Use the light shader object and set the uniforms
		glUseProgram(_lightShader->Program());

		modelLocation = glGetUniformLocation(_lightShader->Program(), "model");
		viewLocation = glGetUniformLocation(_lightShader->Program(), "view");
		projectionLocation = glGetUniformLocation(_lightShader->Program(), "projection");

		_model = glm::translate(_model, _lightPos);
		_model = glm::scale(_model, glm::vec3(0.2f));

		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(_view));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(_projection));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(_model));
		
		glBindVertexArray(_lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

private:
	GLuint _vbo, _vao, _ebo, _lightVAO;
	Shader* _shader;
	Shader* _lightShader;
	Camera* _camera;
	glm::mat4 _model, _view, _projection;
	glm::vec3 _lightPos, _lightColor, _objectColor;
};
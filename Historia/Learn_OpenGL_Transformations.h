#pragma once

#include "Tutorial.h"
#include "stb_image.h"
#include "Shader.h"
#include "InputManager.h"
#include "Command.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Learn_Open_GL_Transformations : public Tutorial
{
public:
	void init_simple()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		stbi_set_flip_vertically_on_load(true);

		_shader = new Shader();
		_shader->CompileShader("Shaders/LearnOpenGL/CoordinateSystems/vertex_shader_1.vert", GL_VERTEX_SHADER);
		_shader->CompileShader("Shaders/LearnOpenGL/Transformations/fragment_shader_1.frag", GL_FRAGMENT_SHADER);
		_shader->LinkShaders();

		GLfloat vertices[] = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
		};

		GLuint indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(6 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(2);

		glGenTextures(2, _textures);
		glBindTexture(GL_TEXTURE_2D, _textures[0]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		loadTexture("media/textures/container.jpg", GL_RGB);
		
		glBindTexture(GL_TEXTURE_2D, _textures[1]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		loadTexture("media/textures/awesomeface.png", GL_RGBA);

		// Coordinate Transformation Stuff
		_model = glm::rotate(_model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0, 0.0f));
		_view = glm::translate(_view, glm::vec3(0.0f, 0.0f, -3.0f));
		_projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	}

	void init()
	{
		_camera = new Camera();
		_camera->setCameraCommands();

		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		stbi_set_flip_vertically_on_load(true);

		_shader = new Shader();
		_shader->CompileShader("Shaders/LearnOpenGL/CoordinateSystems/vertex_shader_1.vert", GL_VERTEX_SHADER);
		_shader->CompileShader("Shaders/LearnOpenGL/Transformations/fragment_shader_1.frag", GL_FRAGMENT_SHADER);
		_shader->LinkShaders();

		float vertices[] = {
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

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(1);

		glGenTextures(2, _textures);
		glBindTexture(GL_TEXTURE_2D, _textures[0]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		loadTexture("media/textures/container.jpg", GL_RGB);

		glBindTexture(GL_TEXTURE_2D, _textures[1]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		loadTexture("media/textures/awesomeface.png", GL_RGBA);

		// Coordinate Transformation Stuff
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0, 0.0f));
		//_view = glm::translate(_view, glm::vec3(0.0f, 0.0f, -3.0f));
		_projection = glm::perspective(glm::radians(45.0f), 16.0f/9.0f, 0.1f, 100.0f);

		
		cubePositions[0] = glm::vec3(0.0f, 0.0f, 0.0f);
		cubePositions[1] = glm::vec3(2.0f, 5.0f, -15.0f);
		cubePositions[2] = glm::vec3(-1.5f, -2.2f, -2.5f);
		cubePositions[3] = glm::vec3(-3.8f, -2.0f, -12.3f);
		cubePositions[4] = glm::vec3(2.4f, -0.4f, -3.5f);
		cubePositions[5] = glm::vec3(-1.7f, 3.0f, -7.5f);
		cubePositions[6] = glm::vec3(1.3f, -2.0f, -2.5f);
		cubePositions[7] = glm::vec3(1.5f, 2.0f, -2.5f);
		cubePositions[8] = glm::vec3(1.5f, 0.2f, -1.5f);
		cubePositions[9] = glm::vec3(-1.3f, 1.0f, -1.5f);

	}

	void loadTexture(const char* path, GLint colorType)
	{
		GLint width, height, nrChannels;
		unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, colorType, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		stbi_image_free(data);
	}

	void update(double currentTime)
	{
		_previousTime = _currentTime;
		_currentTime = currentTime;

		_camera->update(currentTime);
	}

	void render(double currentTime)
	{
		Tutorial::render(currentTime);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glUseProgram(_shader->Program());
		glUniform1i(glGetUniformLocation(_shader->Program(), "texture1"), 0);
		glUniform1i(glGetUniformLocation(_shader->Program(), "texture2"), 1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _textures[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _textures[1]);

		// Transformations
		glm::mat4 trans;

		// Coordinate Systems
		int modelLocation = glGetUniformLocation(_shader->Program(), "model");
		int viewLocation = glGetUniformLocation(_shader->Program(), "view");
		int projectionLocation = glGetUniformLocation(_shader->Program(), "projection");

		_view = _camera->getViewMatrix();
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(_view));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(_projection));

		glBindVertexArray(_vao);
		// Use Draw Elements when using a element buffer object
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;

			if (i % 3 == 0 && i > 0)
			{
				model = glm::rotate(model, (float)currentTime * glm::radians(50.f), glm::vec3(0.5f, 1.0f, 0.0f));
			}
			else
			{
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			}
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// Use Draw Triangles when not using the element buffer and vertices are created in terms of 3 points
		//glDrawArrays(GL_TRIANGLES, 0, 36);
	}


private:
	GLfloat _currentTime = 0.0;
	GLfloat _previousTime = 0.0;

	Camera* _camera;

	// Shader stuff
	Shader* _shader;
	GLuint _textures[2];
	GLuint _ebo, _vao, _vbo;
	glm::mat4 _model, _view, _projection;
	glm::vec3 cubePositions[10];
	

};

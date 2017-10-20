#pragma once
#include "Tutorial.h"
#include "Camera.h"
#include "Shader.h"
#include "stb_image.h"

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
		_lightShader->CompileShader("Shaders/LearnOpenGL/Lighting/MultipleLights/vertex_shader_1.vert", GL_VERTEX_SHADER);
		_lightShader->CompileShader("Shaders/LearnOpenGL/Lighting/MultipleLights/light_shader.frag", GL_FRAGMENT_SHADER);
		_lightShader->LinkShaders();

		_lampShader = new Shader();
		_lampShader->CompileShader("Shaders/LearnOpenGL/Lighting/Materials/vertex_shader_1.vert", GL_VERTEX_SHADER);
		_lampShader->CompileShader("Shaders/LearnOpenGL/Lighting/Materials/lamp_shader.frag", GL_FRAGMENT_SHADER);
		_lampShader->LinkShaders();

		// vertex data containing vertex coordinates and normal values
		GLfloat vertices[] = {
			// positions          // normals           // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
		};

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		_diffuseMap = loadTexture("media/textures/container2.png");
		_specularMap = loadTexture("media/textures/container2_specular.png");
		//_emissionMap = loadTexture("media/textures/matrix.jpg");

		// Light shader objects
		glGenVertexArrays(1, &_lightVAO);
		glBindVertexArray(_lightVAO);

		// We only need to bind to the VBO, the container's VBO's data already contains the correct data
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		// set the vertex aettributes (only position data for the lamp)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
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

		_cubePositions[0] = glm::vec3(0.0f, 0.0f, 0.0f);
		_cubePositions[1] = glm::vec3(2.0f, 5.0f, -15.0f);
		_cubePositions[2] = glm::vec3(-1.5f, -2.2f, -2.5f);
		_cubePositions[3] = glm::vec3(-3.8f, -2.0f, -12.3f);
		_cubePositions[4] = glm::vec3(2.4f, -0.4f, -3.5f);
		_cubePositions[5] = glm::vec3(-1.7f, 3.0f, -7.5f);
		_cubePositions[6] = glm::vec3(1.3f, -2.0f, -2.5f);
		_cubePositions[7] = glm::vec3(1.5f, 2.0f, -2.5f);
		_cubePositions[8] = glm::vec3(1.5f, 0.2f, -1.5f);
		_cubePositions[9] = glm::vec3(-1.3f, 1.0f, -1.5f);

		_pointLightPositions[0] = glm::vec3(0.7f, 0.2f, 2.0f);
		_pointLightPositions[1] = glm::vec3(2.3f, -3.3f, -4.0f);
		_pointLightPositions[2] = glm::vec3(-4.0f, 2.0f, -12.0f);
		_pointLightPositions[3] = glm::vec3(0.0f, 0.2f, -3.0f);
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
		
		/*_lightPos = glm::vec3(sin(currentTime) * 2.5, sin(currentTime) * 2.5, cos(currentTime) * 2.5);
		_model = glm::rotate(_model, -(float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));

		_lightColor.x = sin(currentTime * 2.0f);
		_lightColor.y = sin(currentTime * 0.7f);
		_lightColor.z = sin(currentTime * 1.3f);*/

		glm::vec3 ambientColor = _lightColor * glm::vec3(0.2f);
		glm::vec3 diffuseColor = _lightColor * glm::vec3(0.5f);

		//_lightShader->setMat4("model", _model);
		_lightShader->setMat4("view", _view);
		_lightShader->setMat4("projection", _projection);
		_lightShader->setVec3("viewPos", _camera->position());

		// material properties
		_lightShader->setInt("material.diffuse", 0);
		_lightShader->setInt("material.specular", 1);
		_lightShader->setInt("material.emission", 2);
		_lightShader->setFloat("material.shininess", 32.0f);
		
		// directional light
		_lightShader->setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		_lightShader->setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		_lightShader->setVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
		_lightShader->setVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));

		// point light 1
		_lightShader->setVec3("pointLights[0].position", _pointLightPositions[0]);
		_lightShader->setVec3("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		_lightShader->setVec3("pointLights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		_lightShader->setVec3("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		_lightShader->setFloat("pointLights[0].constant", 1.0f);
		_lightShader->setFloat("pointLights[0].linear", 0.09);
		_lightShader->setFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		_lightShader->setVec3("pointLights[1].position", _pointLightPositions[1]);
		_lightShader->setVec3("pointLights[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		_lightShader->setVec3("pointLights[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		_lightShader->setVec3("pointLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		_lightShader->setFloat("pointLights[1].constant", 1.0f);
		_lightShader->setFloat("pointLights[1].linear", 0.09);
		_lightShader->setFloat("pointLights[1].quadratic", 0.032);
		// point light 3
		_lightShader->setVec3("pointLights[2].position", _pointLightPositions[2]);
		_lightShader->setVec3("pointLights[2].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		_lightShader->setVec3("pointLights[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		_lightShader->setVec3("pointLights[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		_lightShader->setFloat("pointLights[2].constant", 1.0f);
		_lightShader->setFloat("pointLights[2].linear", 0.09);
		_lightShader->setFloat("pointLights[2].quadratic", 0.032);
		// point light 4
		_lightShader->setVec3("pointLights[3].position", _pointLightPositions[3]);
		_lightShader->setVec3("pointLights[3].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		_lightShader->setVec3("pointLights[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		_lightShader->setVec3("pointLights[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		_lightShader->setFloat("pointLights[3].constant", 1.0f);
		_lightShader->setFloat("pointLights[3].linear", 0.09);
		_lightShader->setFloat("pointLights[3].quadratic", 0.032);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _specularMap);
		/*glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _emissionMap);*/

		glBindVertexArray(_vao);

		for (GLuint i = 0; i < 10; ++i)
		{
			_model = glm::mat4();
			_model = glm::translate(_model, _cubePositions[i]);
			GLfloat angle = 20.0f * i;
			_model = glm::rotate(_model, glm::radians(angle), glm::vec3(1.0, 0.3f, 0.5f));
			_lightShader->setMat4("model", _model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// Use the light shader object and set the uniforms
		glUseProgram(_lampShader->Program());
		_lampShader->setMat4("view", _view);
		_lampShader->setMat4("projection", _projection);
		_lampShader->setVec3("lightColor", _lightColor);

		for (int i = 0; i < 4; ++i)
		{
			_model = glm::mat4();
			_model = glm::translate(_model, _pointLightPositions[i]);
			_model = glm::scale(_model, glm::vec3(0.2f));

			_lampShader->setMat4("model", _model);


			glBindVertexArray(_lightVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}		
	}

	GLuint loadTexture(const char* path)
	{
		GLuint textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);

		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			printf("Texture failed to load at path: %s\n", path);
			stbi_image_free(data);
		}

		return textureID;
	}

private:
	GLuint _vbo, _vao, _ebo, _lightVAO;
	GLuint _diffuseMap, _specularMap, _emissionMap;
	Shader* _lightShader;
	Shader* _lampShader;
	Camera* _camera;
	glm::mat4 _model, _view, _projection;
	glm::vec3 _lightPos, _lightColor, _objectColor;
	glm::vec3 _cubePositions[10];
	glm::vec3 _pointLightPositions[4];
};
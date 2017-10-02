#pragma once

#include "Tutorial.h"
#include <cstring>
#include "vmath.h"
#include "stb_image.h"

class Super_Bible_Chapter_5_Textures : public Tutorial
{
public:
	void init_simple_triangle_texture()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		_shader = new Shader();
		_shader->CompileShader("Shaders/Chapter_5/vertex_shader_3.vert", GL_VERTEX_SHADER);
		_shader->CompileShader("Shaders/Chapter_5/fragment_shader_3.frag", GL_FRAGMENT_SHADER);
		_shader->LinkShaders();

		static const GLfloat vertices[] =
		{	 // Positions
			 0.75f, -0.75f, 0.75f, 1.0f,
			-0.75f, -0.75f, 0.75f, 1.0f,
			 0.75f,  0.75f, 0.75f, 1.0f,
		};

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, _buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		// Create a new 2D texture object
		glGenTextures(1, &_texture);

		// Now bind it to the context using the GL_TEXTURE_2D binding point
		glBindTexture(GL_TEXTURE_2D, _texture);

		// Specifiy the amount of storage we want to use for the texture
		glTextureStorage2D(_texture, 1, GL_RGBA32F, 256, 256);

		// Define some data to upload into the texture
		float* data = new float[256 * 256 * 4];

		generate_texture(data, 256, 256);

		// Assume that "texture" is a 2D texture that we created earlier
		glTextureSubImage2D(_texture, 0, 0, 0, 256, 256, GL_RGBA, GL_FLOAT, data);

		// Free the memory we allocated before - OpenGL now has our data
		delete[] data;
	}

	void init()
	{
		bool success = true;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		stbi_set_flip_vertically_on_load(true);

		_shader = new Shader();
		_shader->CompileShader("Shaders/LearnOpenGL/vertex_shader_texture_1.vert", GL_VERTEX_SHADER);
		_shader->CompileShader("Shaders/LearnOpenGL/fragment_shader_texture_1.frag", GL_FRAGMENT_SHADER);
		_shader->LinkShaders();

		GLfloat vertices[] = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.55f, 0.55f,   // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.55f, 0.45f,   // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.45f, 0.45f,   // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.45f, 0.55f    // top left 
		};

		GLuint indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, _buffer);
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
		
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		success = loadTexture("media/textures/container.jpg", GL_RGB);

		glBindTexture(GL_TEXTURE_2D, _textures[1]);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		success = loadTexture("media/textures/awesomeface.png", GL_RGBA);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	bool loadTexture(const char* path, GLint colorFormat)
	{
		bool success = true;

		GLint width, height, nrChannels;
		unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			printf("Failed to load texture: %s\n", path);
			success = false;
		}

		stbi_image_free(data);
		return success;
	}

	void update()
	{

	}

	void render(double currentTime)
	{
		Tutorial::render(currentTime);
		glUseProgram(_shader->Program());
		glUniform1i(glGetUniformLocation(_shader->Program(), "texture1"), 0);
		glUniform1i(glGetUniformLocation(_shader->Program(), "texture2"), 1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _textures[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _textures[1]);

		glBindVertexArray(_vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}


private:
	GLuint _buffer;
	GLuint _ebo;
	GLuint _vao;
	GLuint _texture;
	GLuint _textures[2];
	Shader* _shader;

	void generate_texture(float* data, int width, int height)
	{
		int x, y;

		for (y = 0; y < height; y++)
		{
			for (x = 0; x < width; x++)
			{
				data[(y * width + x) * 4 + 0] = (float)((x & y) & 0xFF) / 255.0f;
				data[(y * width + x) * 4 + 1] = (float)((x | y) & 0xFF) / 255.0f;
				data[(y * width + x) * 4 + 2] = (float)((x ^ y) & 0xFF) / 255.0f;
				data[(y * width + x) * 4 + 3] = 1.0f;
			}
		}
	}


	struct vertex
	{
		// Position
		GLfloat x;
		GLfloat y;
		GLfloat z;
		GLfloat w;
	};
};
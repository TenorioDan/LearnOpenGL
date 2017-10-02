#pragma once

#include "Tutorial.h"
#include <cstring>
#include "vmath.h"
#include "Shader.h"

class Super_Bible_Chapter_5 : public Tutorial
{
public:
	//void init()
	//{
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//	_shader = new Shader();
	//	_shader->CompileShader("Shaders/Chapter_5/vertex_shader_1.vert", GL_VERTEX_SHADER);
	//	_shader->CompileShader("Shaders/Chapter_5/fragment_shader_1.frag", GL_FRAGMENT_SHADER);
	//	_shader->LinkShaders();

	//	// This is the data that we will place into the buffer object
	//	static const vertex vertices[] =
	//	{	 // Positions					// Colors
	//		 0.25f, -0.25f, 0.5f, 1.0f,		1.0f, 0.0f, 0.0f, 1.0f,
	//		-0.25f, -0.25f, 0.5f, 1.0f,		0.0f, 1.0f, 0.0f, 1.0f,	
	//		 0.25f,  0.25f, 0.5f, 1.0f,		0.0f, 0.0f, 1.0f, 1.0f
	//	};


	//	// Create a buffer
	//	//glCreateBuffers(1, &_buffer);

	//	// Specify the data store parameters for the buffer
	//	//glNamedBufferStorage(_buffer, sizeof(vertices) , vertices, GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);

	//	// Now bind it to the context using the GL_ARRAY_BUFFER binding point
	//	//glBindBuffer(GL_ARRAY_BUFFER, _buffer);

	//	
	//	// Put the data into the buffer at offset zero
	//	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(data), data);

	//	// Get a pointer to the buffer's data store
	//	//void* ptr = glMapNamedBuffer(_buffer, GL_WRITE_ONLY);
	//	//void* ptr = glMapNamedBufferRange(_buffer, 0, sizeof(data), GL_MAP_WRITE_BIT);

	//	// Copy our data into it...
	//	//memcpy(ptr, data, sizeof(data));

	//	// Tell OpenGL that we're done with the pointer
	//	//glUnmapNamedBuffer(_buffer);

	//	glCreateVertexArrays(1, &_vao);
	//	//glBindVertexArray(_vao);
	//	
	//	/* Allocate and initialzie a buffer object */
	//	glCreateBuffers(1, &_buffer);
	//	glNamedBufferStorage(_buffer, sizeof(vertices), vertices, GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);

	//	//glNamedBufferStorage(_buffer, sizeof(vertices), vertices, 0);
	//	void* ptr = glMapNamedBufferRange(_buffer, 0, sizeof(vertices), GL_MAP_WRITE_BIT);
	//	memcpy(ptr, vertices, sizeof(vertices));
	//	glUnmapNamedBuffer(_buffer);

	//	/* Set up two vertex attributes - first positions */
	//	glVertexArrayAttribBinding(_vao, 0, 0);
	//	glVertexArrayAttribFormat(_vao, 0, 4, GL_FLOAT, GL_FALSE, offsetof(vertex, x));
	//	glEnableVertexArrayAttrib(_vao, 0);

	//	/* Now colors */
	//	glVertexArrayAttribBinding(_vao, 1, 0);
	//	glVertexArrayAttribFormat(_vao, 1, 4, GL_FLOAT, GL_FALSE, offsetof(vertex, r));
	//	glEnableVertexArrayAttrib(_vao, 1);

	//	glVertexArrayVertexBuffer(_vao, 0, _buffer, 0, 8 * sizeof(GLfloat));
	//	glBindVertexArray(_vao);

	//	// First bind a vertex buffer to the VAO
	//	//glVertexArrayVertexBuffer(_vao, 0, _buffer, 0, 4 * sizeof(GLfloat));

	//	// Now, describe the data to OpenGL, tell it where it is, and turn on automatic vertex fetching
	//	// for the specified vertex attribute
	//	/*glVertexArrayAttribFormat(_vao, 0, 4, GL_FLOAT, GL_FALSE, 0);
	//	glEnableVertexArrayAttrib(_vao, 0);*/

 //	}

	void init()
	{
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		_shader = new Shader();
		_shader->CompileShader("Shaders/Chapter_5/vertex_shader_2.vert", GL_VERTEX_SHADER);
		_shader->CompileShader("Shaders/Chapter_5/fragment_shader_2.frag", GL_FRAGMENT_SHADER);
		_shader->LinkShaders();

		static const GLfloat vertex_positions[] =
		{
			-0.25f,  0.25f, -0.25f, // 0
			-0.25f, -0.25f, -0.25f, // 1
			 0.25f, -0.25f, -0.25f, // 2

			 0.25f, -0.25f, -0.25f, // 2
			 0.25f,  0.25f, -0.25f, // 3
			-0.25f,  0.25f, -0.25f, // 0

			 0.25f, -0.25f, -0.25f, // 2
			 0.25f, -0.25f,  0.25f, // 4
			 0.25f,  0.25f, -0.25f, // 3

			 0.25f, -0.25f,  0.25f, // 4
			 0.25f,  0.25f,  0.25f, // 5
			 0.25f,  0.25f, -0.25f, // 3

			 0.25f, -0.25f,  0.25f, // 4
			-0.25f, -0.25f,  0.25f, // 6
			 0.25f,  0.25f,  0.25f, // 5

			-0.25f, -0.25f,  0.25f, // 6
			-0.25f,  0.25f,  0.25f, // 7
			 0.25f,  0.25f,  0.25f, // 5

			-0.25f, -0.25f,  0.25f, // 6
			-0.25f, -0.25f, -0.25f, // 1
			-0.25f,  0.25f,  0.25f, // 7

			-0.25f, -0.25f, -0.25f, // 1
			-0.25f,  0.25f, -0.25f, // 0
			-0.25f,  0.25f,  0.25f, // 7

			-0.25f, -0.25f,  0.25f, // 6
			 0.25f, -0.25f,  0.25f, // 4
			 0.25f, -0.25f, -0.25f, // 2

			 0.25f, -0.25f, -0.25f, // 2
			-0.25f, -0.25f, -0.25f, // 1
			-0.25f, -0.25f,  0.25f, // 6

			-0.25f,  0.25f, -0.25f, // 0
			 0.25f,  0.25f, -0.25f, // 3
			 0.25f,  0.25f,  0.25f, // 5

			 0.25f,  0.25f,  0.25f, // 5
			-0.25f,  0.25f,  0.25f, // 7
			-0.25f,  0.25f, -0.25f  // 0
		};

		static const GLfloat vertex_positions_reduced[] =
		{
			-0.25f,  0.25f, -0.25f, // 0
			-0.25f, -0.25f, -0.25f, // 1
			 0.25f, -0.25f, -0.25f, // 2
			 0.25f,  0.25f, -0.25f, // 3
			 0.25f, -0.25f,  0.25f, // 4
			 0.25f,  0.25f,  0.25f, // 5
			-0.25f, -0.25f,  0.25f, // 6
			-0.25f,  0.25f,  0.25f, // 7
		};

		static const int indices[] = 
		{
			0, 1, 2,
			2, 3, 0,
			2, 4, 3,
			4, 5, 3,
			4, 6, 5,
			6, 7, 5,
			6, 1, 7,
			1, 0, 7,
			6, 4, 2,
			2, 1, 6,
			0, 3, 5,
			5, 7, 0
		};

		// Generate the vertex array object
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		// Now generate some data and put it in a buffer object
		glGenBuffers(1, &_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, _buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions_reduced), vertex_positions_reduced, GL_STATIC_DRAW);

		glGenBuffers(1, &_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Set up our vertex attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		_mv_location = glGetUniformLocation(_shader->Program(), "mv_matrix");
		_proj_location = glGetUniformLocation(_shader->Program(), "proj_matrix");

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void update()
	{

	}

	void render(double currentTime)
	{
		Tutorial::render(currentTime);

		// Activate our program
		glUseProgram(_shader->Program());
		glBindVertexArray(_vao);

		// Set the projection matrix
		glUniformMatrix4fv(_proj_location, 1, GL_FALSE, _proj_matrix);

			//float f = (float)i + (float)currentTime * 0.3f;
		_mv_matrix = vmath::translate(0.0f, 0.0f, -2.f) *
			vmath::rotate((float)currentTime * 45.0f, 0.0f, 1.0f, 0.0f) *
			vmath::rotate((float)currentTime * 81.0f, 1.0f, 0.0f, 0.0f);

		/*_mv_matrix =
			vmath::translate(0.0f, 0.0f, -10.0f) *
			vmath::rotate((float)currentTime * 45.0f, 0.0f, 1.0f, 0.0f) *
			vmath::rotate((float)currentTime * 81.0f, 1.0f, 0.0f, 0.0f) * 
			vmath::translate(sinf(2.1f * f) * 2.0f * ((float)i) / 24,
				cosf(1.7f * f) * 2.0f * ((float)i) / 24,
				sinf(1.3f * f) * cosf(1.5f * f) * 2.0f);*/

		float aspect = 1.0f;
		_proj_matrix = vmath::perspective(50.0f, aspect, 0.1f, 1000.0f);

		//const GLfloat offset[4] = { sin(currentTime) * 0.5 + 0.5, cos(currentTime) * 0.5 + 0.5f, 0.0f, 0.0f };
		//glUniform4fv(2, 1, offset);

		// Set the model-view and projection matrices
		glUniformMatrix4fv(_mv_location, 1, GL_FALSE, _mv_matrix);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

private:
	// The type used for names in OpenGL is GLuint
	GLuint _buffer;
	GLuint _vao;
	GLuint _ebo;
	Shader* _shader;
	vmath::mat4 _mv_matrix;
	vmath::mat4 _proj_matrix;
	GLuint _mv_location;
	GLuint _proj_location;

	struct vertex
	{
		// Position
		GLfloat x;
		GLfloat y;
		GLfloat z;
		GLfloat w;

		// Color
		GLfloat r;
		GLfloat g;
		GLfloat b;
		GLfloat a;
	};
};
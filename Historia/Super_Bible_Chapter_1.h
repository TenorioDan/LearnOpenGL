#pragma once
#include "Tutorial.h"
#include "Shader.h"

class Super_Bible_Chapter_1 : public Tutorial
{
public:
	~Super_Bible_Chapter_1()
	{
		printf("Deleting Super_Bible_Chapter_1 at %p\n", this);
		glDeleteVertexArrays(1, &_vertexArrayObject);
	};

	void init()
	{
		_shader = new Shader();
		_shader->CompileShader("shaders/intro_pipeline/vertex_shader_1.vert", GL_VERTEX_SHADER);
		/*_shader->CompileShader("shaders/intro_pipeline/tess_control_shader_1.glsl", GL_TESS_CONTROL_SHADER);
		_shader->CompileShader("shaders/intro_pipeline/tess_eval_shader_1.glsl", GL_TESS_EVALUATION_SHADER);
		_shader->CompileShader("shaders/intro_pipeline/geom_shader_1.geom", GL_GEOMETRY_SHADER);*/
		_shader->CompileShader("shaders/intro_pipeline/fragment_shader_3.frag", GL_FRAGMENT_SHADER);
		_shader->LinkShaders();

		glCreateVertexArrays(1, &_vertexArrayObject);
		glBindVertexArray(_vertexArrayObject);

		//glPointSize(5.0f);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void update()
	{

	}

	void render(double currentTime)
	{
		Tutorial::render(currentTime);
		// Use the program object we created earlier for rendering
		glUseProgram(_shader->Program());
		
		GLfloat attrib[] = { (float)sin(currentTime) * 0.5f, 
							 (float)cos(currentTime) * 0.6f, 
							 0.0f, 0.0f };

		const GLfloat triangleAttrib[] = { 0.0f, 0.0f, (float)sin(currentTime), 1.0f };

		// Update the value of input attribute 0
		glVertexAttrib4fv(0, attrib);
		glVertexAttrib4fv(1, triangleAttrib);
		// Draw one triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
private:
	Shader* _shader;
	GLuint _vertexArrayObject;
};
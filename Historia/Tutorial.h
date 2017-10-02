#pragma once
#include <stdio.h>
#include <cmath>
#include "GL_Helpers.h"

class Tutorial
{
public:
	virtual void init() = 0;
	virtual void update() = 0;

	virtual void render(double currentTime)
	{
		/*const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f,
		(float)cos(currentTime) * 0.5f + 0.5f,
		0.f, 1.0f };*/
		const float color[] = { 0.0f, 0.2f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);
		glClearBufferfi(GL_DEPTH_STENCIL, 0, 1.0f, 0);
	}

};
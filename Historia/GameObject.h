#pragma once

#include "GL_Helpers.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameObject
{
public:
	virtual void update(float currentTime)
	{
		_previousTime = _currentTime;
		_currentTime = currentTime;
		_deltaTime = _currentTime - _previousTime;
	}

	virtual void render(glm::mat4 VPMatrix, glm::vec3 viewPos, glm::vec3 lightPos, glm::vec3 lightColor) = 0;

protected:
	float _currentTime;
	float _previousTime;
	float _deltaTime;
};
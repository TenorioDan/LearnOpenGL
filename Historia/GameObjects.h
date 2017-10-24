#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace lights
{
	struct Light
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		int ID;
	};

	struct DirectionalLight : public Light
	{
		glm::vec3 direction;
	};

	struct PointLight : public Light
	{
		glm::vec3 position;

		GLfloat constant;
		GLfloat linear;
		GLfloat quadratic;
	};
}
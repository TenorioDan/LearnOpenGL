#pragma once

#include "Tutorial.h"
#include "Cube.h"
#include "Scene.h"

class Playground : public Tutorial
{
	void init()
	{
		Cube::init();
		_cube1 = new Cube();
		_cube2 = new Cube();
		_cube3 = new Cube();

		_cube1->addTexture("media/textures/container2.png", "media/textures/container2_specular.png", "media/textures/matrix.jpg");
		_cube2->addTexture("media/textures/container2.png", "media/textures/container2_specular.png", NULL);
		_cube3->addTexture("media/textures/container2.png", "media/textures/container2_specular.png", NULL);

		_cubeScene.addGameObject(_cube1);
		_cubeScene.addGameObject(_cube2);
		_cubeScene.addGameObject(_cube3);

		light1.position = glm::vec3(1.0f, 0.0f, 0.0f);
		light1.ambient = glm::vec3(0.05f);
		light1.diffuse = glm::vec3(0.8f);
		light1.specular = glm::vec3(1.0f);
		light1.constant = 1.0f;
		light1.linear = 0.09f;
		light1.quadratic = 0.032f;

		light1.position = glm::vec3(2.0f, 1.0f, 0.5f);
		light1.ambient = glm::vec3(0.05f);
		light1.diffuse = glm::vec3(0.8f);
		light1.specular = glm::vec3(1.0f);
		light1.constant = 1.0f;
		light1.linear = 0.09f;
		light1.quadratic = 0.032f;
		
		_cubeScene.addLight(light1);
	}

	void update(double currentTime)
	{
		_deltaTime = currentTime - _currentTime;
		_currentTime = currentTime;

		Tutorial::update(currentTime);
		_cubeScene.update(currentTime);

		//_cube1->translate(cos(currentTime) * 2.5 * _deltaTime, 0.0f, sin(currentTime) * 2.5 * _deltaTime);
		_cube2->translate(sin(currentTime) * 2.5 * _deltaTime, cos(currentTime) * 2.5 * _deltaTime, 0.0f);
		_cube3->translate(0.0f, cos(currentTime) * 2.5 * _deltaTime, sin(currentTime) * 2.5 * _deltaTime);
	}

	void render(double currentTime)
	{
		Tutorial::render(currentTime);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_cubeScene.render();
	}

private:
	GLfloat _currentTime;
	GLfloat _deltaTime;

	Scene _cubeScene;
	Cube* _cube1;
	Cube* _cube2;
	Cube* _cube3;

	lights::PointLight light1;
};
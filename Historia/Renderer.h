#pragma once

#include "GameObject.h"
#include "Camera.h"

#include <vector>

class Renderer
{
public:
	void init()
	{
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		_camera = new Camera();
		_camera->setCameraCommands();

		_projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
	}

	void update(double currentTime)
	{
		_camera->update(currentTime);

		for (int i = 0; i < _gameObjects.size(); ++i)
		{
			_gameObjects.at(i)->update(currentTime);
		}
	}

	void render()
	{
		glm::mat4 PVMatrix = _projection * _camera->getViewMatrix();

		for (int i = 0; i < _gameObjects.size(); ++i)
		{
			_gameObjects.at(i)->render(PVMatrix, _camera->position(), glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		}
	}

	void addObject(GameObject* gameObject)
	{
		_gameObjects.push_back(gameObject);
	}

private:
	Camera* _camera;

	std::vector<GameObject*> _gameObjects;

	glm::mat4 _projection;

};

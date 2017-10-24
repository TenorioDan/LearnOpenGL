#pragma once

#include "Camera.h"
#include "GameObject.h"
#include "GameObjects.h"

#include <vector>

#define MAX_LIGHTS 100

class Scene
{
public:
	Scene();
	void update(double currentTime);
	void render();

	void addGameObject(GameObject* gameObject);
	void addLight(lights::PointLight& light);

private:
	short int _lightCount;

	Camera _camera;
	Shader _lightShader;
	std::vector<GameObject*> _gameObjects;
	std::vector<lights::PointLight> _pointLights;

	glm::mat4 _projection;
};

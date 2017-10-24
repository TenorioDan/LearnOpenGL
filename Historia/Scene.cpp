#include "Scene.h"
#include <string>

Scene::Scene()
{
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	_lightShader.CompileShader("Shaders/Playground/Lighting/vertex_shader_1.vert", GL_VERTEX_SHADER);
	_lightShader.CompileShader("Shaders/Playground/Lighting/light_shader.frag", GL_FRAGMENT_SHADER);
	_lightShader.LinkShaders();

	_camera.setCameraCommands();

	_projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
}

void Scene::update(double currentTime)
{
	_camera.update(currentTime);
	_lightShader.setVec3("viewPos", _camera.position());

	for (int i = 0; i < _gameObjects.size(); ++i)
	{
		_gameObjects.at(i)->update(currentTime);
	}
}

void Scene::render()
{
	glUseProgram(_lightShader.Program());
	glm::mat4 PVMatrix = _projection * _camera.getViewMatrix();

	for (int i = 0; i < _gameObjects.size(); ++i)
	{
		_gameObjects.at(i)->render(PVMatrix, _lightShader);
	}
}

void Scene::addGameObject(GameObject* gameObject)
{
	_gameObjects.push_back(gameObject);
}


// Add a light to the scenea and update the list of point lights in the fragment shader
void Scene::addLight(lights::PointLight& light)
{
	if (_lightCount < MAX_LIGHTS)
	{
		light.ID = _lightCount;
		std::string shaderString = "pointLights[" + std::to_string(_lightCount++) + "]";
		_pointLights.push_back(light);

		_lightShader.setVec3((shaderString + ".position").c_str(), light.position);
		_lightShader.setVec3((shaderString + ".ambient").c_str(), light.ambient);
		_lightShader.setVec3((shaderString + ".diffuse").c_str(), light.diffuse);
		_lightShader.setFloat((shaderString + ".constant").c_str(), light.constant);
		_lightShader.setFloat((shaderString + ".linear").c_str(), light.linear);
		_lightShader.setFloat((shaderString + ".quadratic").c_str(), light.quadratic);
	}
	else
	{
		printf("Maximum number of lights exceeded\n");
	}
}
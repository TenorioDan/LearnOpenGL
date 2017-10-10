#pragma once

#include "Command.h"
#include "GL_Helpers.h"
#include "InputManager.h"

#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public: 
	Camera();
	~Camera();

	void setCameraCommands();
	void cameraLook(GLfloat xDelta, GLfloat yDelta);
	void cameraStrafe(GLfloat direction);
	void cameraWalk(GLfloat direction);
	void update(float currentTime);

	glm::mat4 getViewMatrix();
	glm::vec3 position();
	glm::vec3 front();
	glm::vec3 up();
	glm::vec3 right();

private:
	InputManager* _inputManager;

	float _currentTime, _previousTime, _deltaTime;

	// Default values
	GLfloat _yawDef = -90.0f;
	GLfloat _pitchDef = 0.0f;
	GLfloat _speedDef = 10.0f;
	GLfloat _sensitivityDef = 0.1f;
	GLfloat _zoomDef = 45.0f;

	GLfloat _yaw = -90.0f;
	GLfloat _pitch = 0.0f;
	GLfloat _speed = 10.0f;
	GLfloat _sensitivity = 0.1f;
	GLfloat _zoom = 45.0f;

	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _worldUp;
	glm::vec3 _right;

	Command* _moveLeftCommand;
	Command* _moveRightCommand;
	Command* _moveForwardCommand;
	Command* _moveBackCommand;
	MouseCommand* _lookCommand;

	void updateCameraVectors();
	
#pragma region Commands
	// Command object specific to this class
	class MoveCommand : public Command
	{
	public:
		enum DIRECTION
		{
			STRAFE,
			WALK
		};

		MoveCommand(Camera* gameObject, DIRECTION direction, GLfloat modifier);
		void Execute();

	private:
		Camera* _camera;
		DIRECTION _direction;
		GLfloat _modifier;
	};

	class LookCommand : public MouseCommand
	{
	public:
		LookCommand(Camera* camera);
		void setMouseState(Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel);
		void Execute();

	private:
		Camera* _camera;
	};
#pragma endregion
};
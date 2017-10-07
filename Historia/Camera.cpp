#include "Camera.h"

Camera::Camera()
{
	// Create the commands so we can delete them later
	_moveLeftCommand = new MoveCommand(this, Camera::MoveCommand::STRAFE, -1);
	_moveRightCommand = new MoveCommand(this, Camera::MoveCommand::STRAFE, 1);
	_moveForwardCommand = new MoveCommand(this, Camera::MoveCommand::WALK, 1);
	_moveBackCommand = new MoveCommand(this, Camera::MoveCommand::WALK, -1);
	_lookCommand = new LookCommand(this);	

	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	_front = glm::vec3(0.0f, 0.0, -1.0f);
	updateCameraVectors();
}

Camera::~Camera()
{
	delete _moveLeftCommand;
	delete _moveRightCommand;
	delete _moveForwardCommand;
	delete _moveBackCommand;
	delete _lookCommand;
}

void Camera::setCameraCommands()
{
	_inputManager = InputManager::getInstance();
	_inputManager->mapKey(SDL_SCANCODE_W, _moveForwardCommand);
	_inputManager->mapKey(SDL_SCANCODE_A, _moveLeftCommand);
	_inputManager->mapKey(SDL_SCANCODE_S, _moveBackCommand);
	_inputManager->mapKey(SDL_SCANCODE_D, _moveRightCommand);
	_inputManager->setMouseMotionCommand(_lookCommand);
}

void Camera::cameraLook(GLfloat xDelta, GLfloat yDelta)
{
	xDelta *= _sensitivity;
	yDelta *= _sensitivity;
	
	_yaw += xDelta;
	_pitch -= yDelta; // add to invert

	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	updateCameraVectors();
}

void Camera::cameraStrafe(GLfloat direction)
{
	_position += _right * _speed * direction;
}

void Camera::cameraWalk(GLfloat direction)
{
	_position += _front * _speed * direction;
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(_position, _position + _front, _up);
}

// Calculates the front vector from the update Eular Angles and
// Uses the Gramm-schmidt process to calculate the up and right vectors
void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front = front;

	_right = glm::normalize(glm::cross(_front, _worldUp));
	_up = glm::normalize(glm::cross(_right, _front));
}

void Camera::update(float currentTime)
{
	_previousTime = _currentTime;
	_currentTime = currentTime;
	_deltaTime = _currentTime - _previousTime;
	_speed = _speedDef * _deltaTime;
}


/* COMMAND CLASS DEFINITIONS  */

#pragma region CameraMoveCommandRegion

Camera::MoveCommand::MoveCommand(Camera* camera, DIRECTION direction, GLfloat modifier)
	: _camera(camera), _direction(direction), _modifier(modifier)
{

}

void Camera::MoveCommand::Execute()
{
	if (_direction == STRAFE)
	{
		_camera->cameraStrafe(_modifier);
	}
	else
	{
		_camera->cameraWalk(_modifier);
	}
}

#pragma endregion

#pragma region CameraLookCommandRegion

Camera::LookCommand::LookCommand(Camera* camera)
	: _camera(camera)
{

};

void Camera::LookCommand::setMouseState(Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel)
{
	_x = x;
	_y = y;
	_xDelta = xrel;
	_yDelta = yrel;
}

void Camera::LookCommand::Execute()
{
	_camera->cameraLook((GLfloat)_xDelta, (GLfloat)_yDelta);
}

#pragma endregion


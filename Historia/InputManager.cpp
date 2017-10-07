#include "InputManager.h"
#include <SDL.h>

InputManager* InputManager::_instance;

InputManager::InputManager() 
{

};

InputManager::~InputManager()
{
	delete _instance;
}

InputManager* InputManager::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new InputManager();
	}

	return _instance;
}

void InputManager::mapKey(SDL_Keycode key, Command* command)
{
	_keyMappings[key] = command;
}

void InputManager::keyPressed(SDL_Keycode key)
{
	if (_keyStates[key])
	{
		receiveKeyboardInput(key);
	}
}

void InputManager::keyReleased(SDL_Keycode key)
{
	// return false;
}

void InputManager::setMouseMotionCommand(MouseCommand* command)
{
	_currentMouseMotionCommand = command;
}

void InputManager::receiveKeyboardInput(SDL_Keycode key)
{
	// In this case, key is does not mean the key in a key/value pair but the SDL Key pressed
	std::map<SDL_Keycode, Command*>::iterator iterator = _keyMappings.find(key);

	if (iterator != _keyMappings.end())
	{
		_commandQueue.push(iterator->second);
	}

}

void InputManager::receiveMouseMotion(SDL_MouseMotionEvent motion)
{
	_currentMouseMotionCommand->setMouseState(motion.xrel, motion.yrel);
	_commandQueue.push(_currentMouseMotionCommand);
}

void InputManager::processInput()
{
	while (!_commandQueue.empty())
	{
		_commandQueue.front()->Execute();
		_commandQueue.pop();
	}
}

// Update keyboard and mouse state
void InputManager::update(float currentTime)
{
	_keyStates = SDL_GetKeyboardState(NULL);
	
	keyPressed(SDL_SCANCODE_W);
	keyPressed(SDL_SCANCODE_A);
	keyPressed(SDL_SCANCODE_S);
	keyPressed(SDL_SCANCODE_D);
}


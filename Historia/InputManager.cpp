#include "InputManager.h"

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

void InputManager::mapKey(Command::CommandKeys key, Command* command)
{
	_keyMappings[key] = command;
}

void InputManager::receiveKeyboardInput(SDL_Keycode key)
{
	switch (key)
	{

	}
}

void InputManager::processInput()
{
	while (!_commandQueue.empty())
	{
		_commandQueue.front()->Execute();
		_commandQueue.pop();
	}
}


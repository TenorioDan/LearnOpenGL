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

void InputManager::mapKey(SDL_Keycode key, Command* command)
{
	_keyMappings[key] = command;
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

void InputManager::processInput()
{
	while (!_commandQueue.empty())
	{
		_commandQueue.front()->Execute();
		_commandQueue.pop();
	}
}


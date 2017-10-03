#pragma once
#include "Command.h"
#include <SDL.h>
#include <map>
#include <queue>

class InputManager
{
public:
	~InputManager();
	static InputManager* getInstance();
	void mapKey(Command::CommandKeys key, Command* command);
	void receiveKeyboardInput(SDL_Keycode key);
	void processInput();

private:
	// Singleton stuff
	InputManager();
	static InputManager* _instance;

	// Class specific
	SDL_Event _sdlEvent;
	std::map<Command::CommandKeys, Command*> _keyMappings;
	std::queue<Command*> _commandQueue;

};
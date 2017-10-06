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
	void mapKey(SDL_Keycode key, Command* command);
	void receiveKeyboardInput(SDL_Keycode key);
	void processInput();
	void update(float currentTime);

	void keyPressed(SDL_Keycode key);
	void keyReleased(SDL_Keycode key);

private:
	// Singleton stuff
	InputManager();
	static InputManager* _instance;

	// Class specific
	const Uint8* _keyStates;
	SDL_Event _sdlEvent;
	std::map<SDL_Keycode, Command*> _keyMappings;
	std::queue<Command*> _commandQueue;

};
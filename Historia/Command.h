#pragma once

class Command
{
public:
	virtual void Execute() = 0;

	enum CommandKeys
	{
		PRESS_W,
		PRESS_A,
		PRESS_S,
		PRESS_D
	};
};
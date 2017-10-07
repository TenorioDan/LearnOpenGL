#pragma once

#include<SDL.h>

class Command
{
public:
	virtual void Execute() = 0;
};

class MouseCommand : public Command
{
public:
	virtual void setMouseState(Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel) = 0;

	Sint32 X()
	{
		return _x;
	}

	Sint32 Y()
	{
		return _y;
	}

protected:
	Sint32 _x, _y, _xDelta, _yDelta;
};
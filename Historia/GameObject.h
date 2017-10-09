#pragma once

class GameObject
{
public:
	virtual void update(float currentTime)
	{
		_previousTime = _currentTime;
		_currentTime = currentTime;
		_deltaTime = _currentTime - _previousTime;
	}

	virtual void render() = 0;

protected:
	float _currentTime;
	float _previousTime;
	float _deltaTime;
};
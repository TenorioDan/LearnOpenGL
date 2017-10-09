#pragma once
#include "GameObject.h"

class Cube : public GameObject
{
public:
	void update(float currentTime);
	void render();
	void init();
};
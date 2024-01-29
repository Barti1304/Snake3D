#pragma once

#include "GameObject.h"

#include <list>
#include <random>

class Apple : public GameObject
{
public:
	Apple(int mSize);

	void moveToRandomPosition(std::list<glm::vec2> positionExceptions);

private:
	int mapSize;
};
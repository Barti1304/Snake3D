#pragma once

#include "Wall.h"

#include <list>

class Map
{
public:
	void render(Cube* cube, Shader* shader, Texture* texture);

	void addWall(Wall w);

	const std::list<Wall>& getWalls();

private:
	std::list<Wall> wallCoords;
};
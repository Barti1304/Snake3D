#include "Map.h"

void Map::render(Cube* cube, Shader* shader, Texture* texture)
{
	for (auto wall : wallCoords)
		wall.render(cube, shader, texture);
}

void Map::addWall(Wall w)
{
	wallCoords.push_back(w);
}

const std::list<Wall>& Map::getWalls()
{
	return wallCoords;
}

#include "Map.h"

void Map::addWall(Wall w)
{
	wallCoords.push_back(w);
}

const std::list<Wall>& Map::getWalls()
{
	return wallCoords;
}

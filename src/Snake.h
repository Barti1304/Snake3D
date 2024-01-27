#pragma once

#include <imgui.h>

#include <glm/glm.hpp>

#include <list>

#include <iostream>

#include "Shader.h"
#include "Cube.h"
#include "Texture.h"

#include "GameObject.h"

#include "Wall.h"

class Snake : public GameObject
{
public:
	Snake(glm::vec2 pos);

	void processInput();

	void update(float deltaTime);

	bool checkCollisionWithItself();
	bool checkColisionWithWalls(std::list<Wall> walls);

	const std::list<glm::vec2>& getBody() { return bodyCoords; }

private:
	void inputCallbackCheck(char c);

	// variables
	char snakeDirection;
	float snakeSpeed;
	int snakeLength;

	std::list<glm::vec2> bodyCoords;

	std::list<int> keystrokes;
};
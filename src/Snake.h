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
	bool checkCollisionWithWalls(std::list<Wall> walls);
	bool checkCollisionWithObject(glm::vec2 pos);

	const std::list<glm::vec2>& getBody();

	int getGameScore();

	void changeLengthBy(int value);

private:
	void inputCallbackCheck(char c);

	int gameScore;

	// variables
	char snakeDirection;
	float snakeSpeed;
	int snakeLength;

	std::list<glm::vec2> bodySegments;

	std::list<int> keystrokes;
};
#pragma once

#include <imgui.h>

#include <glm/glm.hpp>

#include <list>

#include <iostream>

#include "Shader.h"
#include "Cube.h"
#include "Texture.h"

class Snake
{
public:
	Snake(glm::vec2 pos);

	void processInput();

	void update(float deltaTime);
	void render(Cube* cube, Shader* shader, Texture* texture);

	glm::vec2 getSnakePos() const { return snakePosition; }
	char getSnakeDirection() const { return snakeDirection; }

	bool checkCollisions();

private:
	glm::vec2 snakePosition;
	char snakeDirection;
	float snakeSpeed;
	int snakeLength;

	std::list<glm::vec2> bodyCoords;

	std::list<int> keystrokes;
};
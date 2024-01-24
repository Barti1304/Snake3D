#pragma once

#include <glm/glm.hpp>

#include <list>

#include <GLFW/glfw3.h>
#include <imgui.h>

#include <iostream>

class Snake
{
public:
	Snake(glm::vec2 pos);

	void processInput();

	void update(float deltaTime);

	glm::vec2 getSnakePos() const;

private:
	char snakeDirection;
	float snakeSpeed;

	glm::vec2 snakePosition;
	std::list<glm::vec2> bodyPosition;

	std::list<int> keystrokes;
};
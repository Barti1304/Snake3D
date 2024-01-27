#pragma once

#include <imgui.h>

#include <glm/glm.hpp>

#include <list>

#include <iostream>

#include "Shader.h"
#include "Cube.h"
#include "Texture.h"

#include "GameObject.h"

class Snake : public GameObject
{
public:
	Snake(glm::vec2 pos);

	void processInput();

	void update(float deltaTime);
	void render(Cube* cube, Shader* shader, Texture* texture);

	bool checkCollisions();

private:
	void inputCallbackCheck(char c);

	//variables
	char snakeDirection;
	float snakeSpeed;
	int snakeLength;

	std::list<glm::vec2> bodyCoords;

	std::list<int> keystrokes;
};
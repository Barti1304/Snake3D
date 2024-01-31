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
	Snake(float speed);

	void processInput();

	void update(float deltaTime);

	bool checkCollisionWithItself();
	bool checkCollisionWithWalls(std::list<Wall> walls);
	bool checkCollisionWithObject(glm::vec2 pos);

	const std::list<glm::vec2>& getBody();

	int getLength();
	void changeLengthBy(int value);

	void die();
	bool isSnakeDead() const;

private:
	void inputCallbackCheck(char c);

	bool isDead;


	// these are for saving beginning cell positions (gotta check them later)
	bool checkSavedPos;
	int xSavedPos;
	int ySavedPos;


	// variables
	char snakeDirection;
	float snakeSpeed;
	int snakeLength;

	std::list<glm::vec2> bodySegments;

	std::list<int> keystrokes;
};
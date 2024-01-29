#include "Snake.h"

Snake::Snake(glm::vec2 pos)
{
	GM_position = pos;

	snakeDirection = 'd';
	snakeSpeed = 2.5f;
	snakeLength = 3;

	gameScore = 0;
}

void Snake::processInput()
{
	if (ImGui::IsKeyPressed(ImGuiKey_W))
		this->inputCallbackCheck('w');

	if (ImGui::IsKeyPressed(ImGuiKey_A))
		this->inputCallbackCheck('a');

	if (ImGui::IsKeyPressed(ImGuiKey_S))
		this->inputCallbackCheck('s');

	if (ImGui::IsKeyPressed(ImGuiKey_D))
		this->inputCallbackCheck('d');
}

void Snake::update(float deltaTime)
{
	// direction
	static int xSavedPos{ (int)GM_position.x * 100 };
	static int ySavedPos{ (int)GM_position.y * 100 };

	int xSnakePos = int(GM_position.x * 100);
	int ySnakePos = int(GM_position.y * 100);
	
	bool xGridCheck = std::abs(xSavedPos - xSnakePos) > 100;
	bool yGridCheck = std::abs(ySavedPos - ySnakePos) > 100;

	// remove repeated keystrokes (one after another)
	while (keystrokes.size())
	{
		if (snakeDirection == keystrokes.front())
			keystrokes.pop_front();
		else
			break;
	}

	// snake cannot be able to turn 180 degrees in any direction
	while (keystrokes.size())
	{
		if (snakeDirection == 'w' && keystrokes.front() == 's'
			|| snakeDirection == 'a' && keystrokes.front() == 'd'
			|| snakeDirection == 's' && keystrokes.front() == 'w'
			|| snakeDirection == 'd' && keystrokes.front() == 'a')
		{
			keystrokes.pop_front();
		}
		else
			break;
	}

	// if snake is aligned to the grid - turn if any keystrokes are registered
	if (keystrokes.size())
	{
		if (xGridCheck || yGridCheck)
		{
			snakeDirection = keystrokes.front();
			keystrokes.pop_front();
		}
	}

	// align snake position to x axis (for adding its body part by grid)
	if (xGridCheck)
	{
		xSavedPos += (xSavedPos > xSnakePos) ? -100 : 100;
		
		if (xSavedPos)
			GM_position.x = float(xSavedPos / 100);
		else
			GM_position.x = 0;
	}
	
	// align snake position to y axis (for adding its body part by grid)
	if (yGridCheck)
	{
		ySavedPos += (ySavedPos > ySnakePos) ? -100 : 100;

		if (ySavedPos)
			GM_position.y = float(ySavedPos / 100);
		else
			GM_position.y = 0;
	}


	// snake body
	if (xGridCheck || yGridCheck)
	{
		bool canBeAdded{ true };

		for (const auto& bodySegment : bodySegments)
		{
			if (GM_position.x == bodySegment.x && GM_position.y == bodySegment.y)
			{
				canBeAdded = false;
				break;
			}
		}

		if (canBeAdded)
			bodySegments.push_back(GM_position);
	}


	// snake body lenght
	if (bodySegments.size() > snakeLength)
		bodySegments.pop_front();


	// movement
	switch (snakeDirection)
	{
	case 'w':
		GM_position += glm::vec2(0, 1) * snakeSpeed * deltaTime;
		break;
	case 'a':
		GM_position -= glm::vec2(1, 0) * snakeSpeed * deltaTime;
		break;
	case 's':
		GM_position -= glm::vec2(0, 1) * snakeSpeed * deltaTime;
		break;
	case 'd':
		GM_position += glm::vec2(1, 0) * snakeSpeed * deltaTime;
	}
}

bool Snake::checkCollisionWithItself()
{
	for (const auto& bodySegment : bodySegments)
	{
		bool isTouchingBodySegment
		{
			GM_position.x > bodySegment.x - 0.5f
			&& GM_position.x < bodySegment.x + 0.5f
			&& GM_position.y > bodySegment.y - 0.5f
			&& GM_position.y < bodySegment.y + 0.5f
		};

		if (isTouchingBodySegment && bodySegment != bodySegments.back())
			return true;
	};

	return false;
}

bool Snake::checkCollisionWithWalls(std::list<Wall> walls)
{
	for (const auto& wall : walls)
	{
		bool isTouchingBodySegment
		{
			GM_position.x > wall.getPosition().x - 0.5f
			&& GM_position.x < wall.getPosition().x + 0.5f
			&& GM_position.y > wall.getPosition().y - 0.5f
			&& GM_position.y < wall.getPosition().y + 0.5f
		};

		if (isTouchingBodySegment)
			return true;
	};

	return false;
}

bool Snake::checkCollisionWithObject(glm::vec2 pos)
{
	bool isTouchingBodySegment
	{
		GM_position.x > pos.x - 0.5f
		&& GM_position.x < pos.x + 0.5f
		&& GM_position.y > pos.y - 0.5f
		&& GM_position.y < pos.y + 0.5f
	};

	return isTouchingBodySegment;
}

const std::list<glm::vec2>& Snake::getBody()
{
	return bodySegments;
}

int Snake::getGameScore()
{
	return (int(bodySegments.size() - 3) < 0) ? 0 : int(bodySegments.size() - 3);
}

void Snake::changeLengthBy(int value)
{
	snakeLength += value;
}

void Snake::inputCallbackCheck(char c)
{
	if (keystrokes.size())
	{
		if (keystrokes.back() != c)
			keystrokes.push_back(c);
	}
	else
		keystrokes.push_back(c);
}
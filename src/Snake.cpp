#include "Snake.h"

Snake::Snake(glm::vec2 pos)
{
	snakePosition = pos;
	snakeDirection = 'd';
	snakeSpeed = 1.5f;
}

void Snake::processInput()
{
	if (ImGui::IsKeyPressed(ImGuiKey_W))
		keystrokes.push_back('w');

	if (ImGui::IsKeyPressed(ImGuiKey_A))
		keystrokes.push_back('a');
	
	if (ImGui::IsKeyPressed(ImGuiKey_S))
		keystrokes.push_back('s');
	
	if (ImGui::IsKeyPressed(ImGuiKey_D))
		keystrokes.push_back('d');
}

void Snake::update(float deltaTime)
{
	// direction
	static int xSavedPos{ 0 };
	static int ySavedPos{ 0 };

	int xSnakePos = int(snakePosition.x * 100.0f);
	int ySnakePos = int(snakePosition.y * 100.0f);
	
	bool xGridCheck = std::abs(xSavedPos - xSnakePos) > 100;
	bool yGridCheck = std::abs(ySavedPos - ySnakePos) > 100;

	if (keystrokes.size())
	{
		for (char elem : keystrokes)
			std::cout << elem << ' ';
		std::cout << '\n';

		while (keystrokes.size())
		{
			if (snakeDirection == keystrokes.front())
				keystrokes.pop_front();
			else
				break;
		}

		// snake should not be able to turn 180 degrees in any direction (to be finished)
		/*while (keystrokes.size())
		{
			if (snakeDirection == 'w' && keystrokes.front() == 's')
				keystrokes.pop_front();
			else 
				break;
		}*/

		if (xGridCheck || yGridCheck)
		{
			snakeDirection = keystrokes.front();
			keystrokes.pop_front();
		}
	}

	if (xGridCheck)
	{
		xSavedPos += (xSavedPos > xSnakePos) ? -100 : 100;
		
		if (xSavedPos)
			snakePosition.x = float(xSavedPos / 100);
		else
			snakePosition.x = 0;
	}
	
	if (yGridCheck)
	{
		ySavedPos += (ySavedPos > ySnakePos) ? -100 : 100;

		if (ySavedPos)
			snakePosition.y = float(ySavedPos / 100);
		else
			snakePosition.y = 0;
	}


	// movement
	switch (snakeDirection)
	{
	case 'w':
		snakePosition += glm::vec2(0, 1) * snakeSpeed * deltaTime;
		break;
	case 'a':
		snakePosition -= glm::vec2(1, 0) * snakeSpeed * deltaTime;
		break;
	case 's':
		snakePosition -= glm::vec2(0, 1) * snakeSpeed * deltaTime;
		break;
	case 'd':
		snakePosition += glm::vec2(1, 0) * snakeSpeed * deltaTime;
	}
}

glm::vec2 Snake::getSnakePos() const
{
	return snakePosition;
}
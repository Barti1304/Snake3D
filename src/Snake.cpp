#include "Snake.h"

Snake::Snake(glm::vec2 pos)
{
	GM_position = pos;

	snakeDirection = 'd';
	snakeSpeed = 2.5f;
	snakeLength = 4;
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

		for (const auto& bodySegment : bodyCoords)
		{
			if (GM_position.x == bodySegment.x && GM_position.y == bodySegment.y)
			{
				canBeAdded = false;
				break;
			}
		}

		if (canBeAdded)
			bodyCoords.push_back(GM_position);
	}


	// snake body lenght
	if (bodyCoords.size() > snakeLength)
		bodyCoords.pop_front();


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

void Snake::render(Cube* cube, Shader* shader, Texture* texture)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(GM_position, 0));

	shader->use();
	shader->setMat4("model", model);
	
	texture->bindTexture();

	cube->render(shader);

	for (const auto& bodyPos : bodyCoords)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(bodyPos, 0));
		
		shader->setMat4("model", model);

		cube->render(shader);
	}
}

bool Snake::checkCollisions()
{
	for (const auto& bodySegment : bodyCoords)
	{
		bool isTouchingBodySegment
		{
			GM_position.x > bodySegment.x - 0.5f
			&& GM_position.x < bodySegment.x + 0.5f
			&& GM_position.y > bodySegment.y - 0.5f
			&& GM_position.y < bodySegment.y + 0.5f
		};

		if (isTouchingBodySegment && bodySegment != bodyCoords.back())
			return true;
	};

	return false;
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
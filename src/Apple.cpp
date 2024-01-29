#include "Apple.h"

Apple::Apple(int mSize)
{
	mapSize = mSize;
}

void Apple::moveToRandomPosition(std::list<glm::vec2> positionExceptions)
{
	std::random_device rd;
	std::uniform_int_distribution<int> dist(-(mapSize / 2), (mapSize / 2));

	glm::vec2 newPosition{};

	while (true)
	{
		newPosition = { dist(rd), dist(rd) };

		int counter{};
		for (auto posEx : positionExceptions)
			if (newPosition != posEx)
				counter++;

		if (counter == positionExceptions.size())
			break;
	}

	GM_position = newPosition;
}

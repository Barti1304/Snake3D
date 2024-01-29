#pragma once

#include <glm/glm.hpp>

class GameObject
{
public:
	glm::vec2 getPosition() const;

protected:
	glm::vec2 GM_position;
};
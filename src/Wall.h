#pragma once

#include "Shader.h"
#include "Cube.h"
#include "Texture.h"

#include "GameObject.h"

class Wall : public GameObject
{
public:
	Wall(glm::vec2 pos);

	void render(Cube* cube, Shader* shader, Texture* texture);
};
#pragma once

#include <glad/glad.h>

#include "Shader.h"

class Cube
{
public:
	Cube();
	void render(Shader* shader);

private:
	unsigned int vao, vbo;
};
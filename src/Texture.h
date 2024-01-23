#pragma once

#include <glad/glad.h>

class Texture
{
public:
	Texture(const char* path);

	void bindTexture();

private:
	unsigned int texture;
};
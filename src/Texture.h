#pragma once

#include <glad/glad.h>

class Texture
{
public:
	Texture(const char* path);

	void bindTexture();

	unsigned int getID();

private:
	unsigned int texture;
};
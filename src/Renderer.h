#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Cube.h"
#include "Texture.h"

class Renderer
{
public:
	Renderer();

	void setShader(Shader* sh);
	void setTexture(Texture* tex);

	void setInt(const char* uniform, int value);
	void setFloat(const char* uniform, float value);
	void setVec3(const char* uniform, glm::vec3 value);
	void setMat4(const char* uniform, glm::mat4 value);

	void renderCube(glm::vec2 pos);

private:
	Cube* cube;

	Shader* shader;
	Texture* texture;
};
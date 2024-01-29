#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Cube.h"
#include "Texture.h"

#include <string>
#include <unordered_map>

class Renderer
{
public:
	Renderer();

	void addShader(Shader* shader, std::string id);
	void addTexture(Texture* texture, std::string id);

	void setActiveShader(std::string id);
	void setActiveTexture(std::string id);

	void setInt(const char* uniform, int value);
	void setFloat(const char* uniform, float value);
	void setVec3(const char* uniform, glm::vec3 value);
	void setMat4(const char* uniform, glm::mat4 value);

	void renderCube(glm::vec2 pos);

private:
	Cube* cube;

	Shader* activeShader;
	Texture* activeTexture;

	std::unordered_map<std::string, Shader*> shaderMap;
	std::unordered_map<std::string, Texture*> textureMap;
};
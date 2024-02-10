#include "Renderer.h"

Renderer::Renderer()
{
	cube = new Cube();

	activeShader = nullptr;
	activeTexture = nullptr;
}

void Renderer::addShader(Shader* shader, std::string id)
{
	shaderMap.insert({ id, shader });
}

void Renderer::addTexture(Texture* texture, std::string id)
{
	textureMap.insert({ id, texture });
}

void Renderer::setActiveShader(std::string id)
{
	if (shaderMap.find(id) != shaderMap.end())
	{
		activeShader = shaderMap.at(id);
		activeShader->use();
	}
	else
		std::cout << "[RENDERER : ERROR] - no shader with id: '" << id << "' has been found!\n";
}

void Renderer::setActiveTexture(std::string id)
{
	if (textureMap.find(id) != textureMap.end())
	{
		activeTexture = textureMap.at(id);
		activeTexture->bindTexture();
	}
	else
		std::cout << "[RENDERER : ERROR] - no texture with id: '" << id << "' has been found!\n";
}

Shader* Renderer::getShader(std::string id)
{
	if (shaderMap.find(id) != shaderMap.end())
		return shaderMap.at(id);

	return 0;
}

Texture* Renderer::getTexture(std::string id)
{
	if (textureMap.find(id) != textureMap.end())
		return textureMap.at(id);

	return 0;
}

void Renderer::setInt(const char* uniform, int value)
{
	activeShader->setInt(uniform, value);
}

void Renderer::setFloat(const char* uniform, float value)
{
	activeShader->setFloat(uniform, value);
}

void Renderer::setVec3(const char* uniform, glm::vec3 value)
{
	activeShader->setVec3(uniform, value);
}

void Renderer::setMat4(const char* uniform, glm::mat4 value)
{
	activeShader->setMat4(uniform, value);
}

void Renderer::renderCube(glm::vec2 pos)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(pos, 0));

	activeShader->setMat4("model", model);

	cube->render(activeShader);
}

void Renderer::renderCube(glm::vec3 pos)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, pos);

	activeShader->setMat4("model", model);

	cube->render(activeShader);
}
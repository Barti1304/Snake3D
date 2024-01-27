#include "Renderer.h"

Renderer::Renderer()
{
	cube = new Cube();

	shader = nullptr;
	texture = nullptr;
}

void Renderer::setShader(Shader* sh)
{
	shader = sh;
	shader->use();
}

void Renderer::setTexture(Texture* tex)
{
	texture = tex;
	texture->bindTexture();
}

void Renderer::setInt(const char* uniform, int value)
{
	shader->setInt(uniform, value);
}

void Renderer::setFloat(const char* uniform, float value)
{
	shader->setFloat(uniform, value);
}

void Renderer::setVec3(const char* uniform, glm::vec3 value)
{
	shader->setVec3(uniform, value);
}

void Renderer::setMat4(const char* uniform, glm::mat4 value)
{
	shader->setMat4(uniform, value);
}

void Renderer::renderCube(glm::vec2 pos)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(pos, 0));

	shader->setMat4("model", model);

	cube->render(shader);
}
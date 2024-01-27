#include "Wall.h"

Wall::Wall(glm::vec2 pos)
{
	GM_position = pos;
}

void Wall::render(Cube* cube, Shader* shader, Texture* texture)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(GM_position, 0));

	shader->use();
	shader->setMat4("model", model);

	texture->bindTexture();
	cube->render(shader);
}

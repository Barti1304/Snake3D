#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
	float constant, float linear, float quadratic, float cutOff, float outerCutOff)
	: Light(ambient, diffuse, specular)
{
	this->position = position;
	this->direction = direction;

	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;

	this->cutOff = glm::cos(glm::radians(cutOff));
	this->outerCutOff = glm::cos(glm::radians(outerCutOff));
}

void SpotLight::setPosition(glm::vec3 position)
{
	this->position = position;
}

void SpotLight::updateLightData(Shader* shader)
{
	shader->use();

	shader->setVec3("spotLight.position", position);
	shader->setVec3("spotLight.direction", direction);

	shader->setVec3("spotLight.ambient", ambient);
	shader->setVec3("spotLight.diffuse", diffuse);
	shader->setVec3("spotLight.specular", specular);

	shader->setFloat("spotLight.constant", constant);
	shader->setFloat("spotLight.linear", linear);
	shader->setFloat("spotLight.quadratic", quadratic);

	shader->setFloat("spotLight.cutOff", cutOff);
	shader->setFloat("spotLight.outerCutOff", outerCutOff);
}
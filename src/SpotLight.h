#pragma once

#include "Light.h"

class SpotLight : public Light
{
public:
	SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
		float constant, float linear, float quadratic, float cutOff, float outerCutOff);

	void setPosition(glm::vec3 position);

	void updateLightData(Shader* shader) override;

private:
	glm::vec3 position;
	glm::vec3 direction;

	float constant;
	float linear;
	float quadratic;

	float cutOff;
	float outerCutOff;
};
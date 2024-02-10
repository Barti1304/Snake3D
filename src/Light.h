#pragma once

#include <glm/glm.hpp>

#include "Shader.h"

class Light
{
public:
	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

	virtual void updateLightData(Shader* shader) = 0;

protected:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};
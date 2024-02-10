#pragma once

#include <glm/glm.hpp>

class Light
{
public:
	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

protected:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};
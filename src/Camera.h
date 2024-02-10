#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera(float fov, glm::vec3 pos);

	glm::vec3 getPosition();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	
private:
	glm::vec3 cameraPosition;
	float cameraFOV;
};
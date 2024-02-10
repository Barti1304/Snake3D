#include "Camera.h"

Camera::Camera(float fov, glm::vec3 pos)
{
	cameraFOV = fov;
	cameraPosition = pos;
}

glm::vec3 Camera::getPosition()
{
	return cameraPosition;
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(cameraPosition, cameraPosition + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
}

glm::mat4 Camera::getProjectionMatrix()
{
	return glm::perspective(glm::radians(cameraFOV), 1.0f, 0.1f, 100.0f);
}

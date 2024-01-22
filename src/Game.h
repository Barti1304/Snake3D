#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdlib>

#include "Shader.h"
#include "Cube.h"
#include "Camera.h"

class Game
{
public:
	Game(int wWidth, int wHeight, const char* wTitle);
	~Game();

	void run();

private:
	void update();
	void render();

	void initOpenGL(int wWidth, int wHeight, const char* wTitle);
	void initShader(const char* vPath, const char* fPath);
	void initCube();
	void initCamera(float fov, glm::vec3 pos);

	// variables
	GLFWwindow* window;
	Shader* shader;
	Cube* cube;
	Camera* camera;
};
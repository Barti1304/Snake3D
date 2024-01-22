#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdlib>

#include "Shader.h"

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

	// variables
	GLFWwindow* window;
	Shader* shader;
	unsigned int vao, vbo;
};
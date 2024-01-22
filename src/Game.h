#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdlib>

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

	// variables
	GLFWwindow* window;
};
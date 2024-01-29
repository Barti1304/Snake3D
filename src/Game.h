#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// it has easier to use input functions than glfw :3
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <cstdlib>

#include "Shader.h"
#include "Cube.h"
#include "Camera.h"
#include "Texture.h"
#include "Snake.h"
#include "Map.h"
#include "Apple.h"

#include "Renderer.h"

class Game
{
public:
	Game(int wWidth, int wHeight, const char* wTitle);
	~Game();

	void run();

private:
	void update();
	void render();

	void updateDeltaTime();
	void processInput();

	void initOpenGL(int wWidth, int wHeight, const char* wTitle);
	void initCamera(float fov, glm::vec3 pos);
	void initSnake(glm::vec2 pos);
	void initMap();
	void initApple();

	void initRenderer();
	
	void initImGui();
	void newFrameImGui();
	void displayImGuiContent();
	void renderImGui();
	void shutdownImGui();

	// variables
	Renderer* renderer;

	GLFWwindow* window;
	Camera* camera;
	Snake* snake;
	Map* map;
	Apple* apple;

	float deltaTime;
};
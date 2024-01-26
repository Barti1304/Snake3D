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
	void initShader(const char* vPath, const char* fPath);
	void initCube();
	void initCamera(float fov, glm::vec3 pos);
	void initTextures();
	void initSnake(glm::vec2 pos);
	
	void initImGui();
	void newFrameImGui();
	void displayImGuiContent();
	void renderImGui();
	void shutdownImGui();

	// variables
	GLFWwindow* window;
	Shader* shader;
	Cube* cube;
	Camera* camera;
	Texture* tex_snake;
	Snake* snake;

	float deltaTime;
};
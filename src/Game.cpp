#include "Game.h"

void framebuffersizecallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Game::Game(int wWidth, int wHeight, const char* wTitle)
{
	this->initOpenGL(wWidth, wHeight, wTitle);
	this->initShader("./shaders/shader.vert", "./shaders/shader.frag");
	this->initCube();
	this->initCamera(45.0f, glm::vec3(0, 0, -10));
	this->initTextures();
}

Game::~Game()
{
	delete shader;
	delete cube;
	delete camera;

	glfwDestroyWindow(window);
	glfwTerminate();
}

void Game::run()
{
	while (!glfwWindowShouldClose(window))
	{
		this->update();
		this->render();
	}
}

void Game::update()
{
	glfwPollEvents();

	//

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0, 3, 0));
	
	shader->use();
	shader->setMat4("model", model);
	shader->setMat4("view", camera->getViewMatrix());
	shader->setMat4("projection", camera->getProjectionMatrix());
}

void Game::render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	tex_snake->bindTexture();

	cube->render(shader);

	glfwSwapBuffers(window);
}

void Game::initOpenGL(int wWidth, int wHeight, const char* wTitle)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(wWidth, wHeight, wTitle, 0, 0);

	if (!window)
	{
		glfwTerminate();
		std::exit(-1);
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffersizecallback);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
		std::exit(-1);

	glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);
}

void Game::initShader(const char* vPath, const char* fPath)
{
	shader = new Shader(vPath, fPath);
}

void Game::initCube()
{
	cube = new Cube();
}

void Game::initCamera(float fov, glm::vec3 pos)
{
	camera = new Camera(fov, pos);
}

void Game::initTextures()
{
	tex_snake = new Texture("./res/snake.png");
}
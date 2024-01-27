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
	
	this->initCamera(60.0f, glm::vec3(0, 0, 15));
	
	this->initTextures();
	
	this->initImGui();

	// begin from (-1, 0) to place 1st body segment on (0, 0)
	this->initSnake(glm::vec2(-1, 0));
}

Game::~Game()
{
	delete shader;
	delete cube;
	delete camera;
	delete tex_snake;
	
	// causes errors on exit
	// delete cube;

	this->shutdownImGui();

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
	this->updateDeltaTime();

	//

	glfwPollEvents();

	this->processInput();

	// 

	snake->update(deltaTime);
	
	if (snake->checkCollisions())
	{
		std::cout << "Collision detected!\n" << snake->getPosition().x << " x " << snake->getPosition().y << '\n';

		std::exit(1);
	}

	//
	
	shader->use();
	shader->setMat4("view", camera->getViewMatrix());
	shader->setMat4("projection", camera->getProjectionMatrix());
}

void Game::render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->newFrameImGui();

	//

	snake->render(cube, shader, tex_snake);

	//

	this->displayImGuiContent();
	this->renderImGui();

	glfwSwapBuffers(window);
}

void Game::updateDeltaTime()
{
	static float lastFrame;
	deltaTime = (float)glfwGetTime() - lastFrame;
	lastFrame = (float)glfwGetTime();
}

void Game::processInput()
{
	// exit
	if (ImGui::IsKeyPressed(ImGuiKey_Escape))
		glfwSetWindowShouldClose(window, true);

	// snake controls
	snake->processInput();
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

void Game::initSnake(glm::vec2 pos)
{
	snake = new Snake(pos);
}

void Game::initImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void Game::newFrameImGui()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Game::displayImGuiContent()
{
	ImGui::Begin("Debug");

	ImGui::Text("Snake head pos: [%.2f, %.2f]", snake->getPosition().x, snake->getPosition().y);

	ImGui::End();
}

void Game::renderImGui()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Game::shutdownImGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
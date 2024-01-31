#include "Game.h"

void framebuffersizecallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Game::Game(int wWidth, int wHeight, const char* wTitle)
{
	isPaused = false;
	isConfig = true;

	//

	this->loadHighscore();

	//

	this->initOpenGL(wWidth, wHeight, wTitle);
			
	this->initCamera(60.0f, glm::vec3(0, 0, 15));
		
	this->initImGui();

	this->initSnake();

	this->initMap();

	this->initApple();

	//

	this->initRenderer();
}

Game::~Game()
{
	this->saveHighscore();

	//

	delete renderer;
	delete camera;
	delete snake;
	delete map;
	delete apple;
	
	//

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
	this->updateGameScore();

	this->updateDeltaTime();

	//

	glfwPollEvents();

	this->processInput();

	// 

	if (!isPaused && !isConfig)
		snake->update(deltaTime);

	if (snake->checkCollisionWithItself() || snake->checkCollisionWithWalls(map->getWalls()))
		snake->die();

	if (snake->checkCollisionWithObject(apple->getPosition()))
	{
		apple->moveToRandomPosition(snake->getBody());
		snake->changeLengthBy(1);
	}
}

void Game::render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->newFrameImGui();

	//

	renderer->setActiveShader("shader");
	renderer->setMat4("view", camera->getViewMatrix());
	renderer->setMat4("projection", camera->getProjectionMatrix());


	// render walls
	renderer->setActiveTexture("tex_wall");

	for (const auto& wall : map->getWalls())
		renderer->renderCube(wall.getPosition());


	// render snake
	renderer->setActiveTexture("tex_snake");

	renderer->renderCube(snake->getPosition());

	for (const auto& bodySegmentPos : snake->getBody())
		renderer->renderCube(bodySegmentPos);


	// render apple
	renderer->setActiveTexture("tex_apple");

	renderer->renderCube(apple->getPosition());


	// render grass
	renderer->setActiveTexture("tex_grass");

	for (int y = -7; y <= 7; y++)
		for (int x = -7; x <= 7; x++)
			renderer->renderCube(glm::vec3(x, y, -1));


	this->displayImGuiContent();
	this->renderImGui();

	glfwSwapBuffers(window);
}

void Game::updateGameScore()
{
	gameScore = (int(snake->getLength() - 3) < 0) ? 0 : int(snake->getLength() - 3);

	if (!snake->isSnakeDead() && gameScore > gameHighscore)
		gameHighscore = gameScore;
}

void Game::updateDeltaTime()
{
	static float lastFrame;
	deltaTime = (float)glfwGetTime() - lastFrame;
	lastFrame = (float)glfwGetTime();
}

void Game::processInput()
{
	// pause
	if (ImGui::IsKeyPressed(ImGuiKey_Escape) && !isConfig && !snake->isSnakeDead())
		isPaused = !isPaused;

	// snake controls
	if (!isPaused && !isConfig) 
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

void Game::initCamera(float fov, glm::vec3 pos)
{
	camera = new Camera(fov, pos);
}

void Game::initSnake()
{
	snake = new Snake(config_snakeSpeed);
}

void Game::initMap()
{
	map = new Map();
	
	for (int x = -8; x <= 8; x++)
	{
		map->addWall(Wall({ x, -8 }));
		map->addWall(Wall({ x, 8 }));
	}

	for (int y = -7; y <= 7; y++)
	{
		map->addWall(Wall({-8, y}));
		map->addWall(Wall({8, y}));
	}
}

void Game::initApple()
{
	apple = new Apple(15);
	apple->moveToRandomPosition(snake->getBody());
}

void Game::initRenderer()
{
	renderer = new Renderer();

	// init shaders
	renderer->addShader(new Shader("./shaders/shader.vert", "./shaders/shader.frag"), "shader");

	// init textures
	renderer->addTexture(new Texture("./res/snake.png"), "tex_snake");
	renderer->addTexture(new Texture("./res/wall.png"), "tex_wall");
	renderer->addTexture(new Texture("./res/apple.png"), "tex_apple");
	renderer->addTexture(new Texture("./res/grass.png"), "tex_grass");
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
	this->displayScore();

	if (isConfig)
		this->displayGameConfig();

	if (isPaused)
		this->displayPause();

	if (snake->isSnakeDead())
		this->displayGameOver();
}

void Game::displayGameConfig()
{
	ImGui::SetNextWindowPos({ 200, 200 });
	ImGui::SetNextWindowSize({ 200, 200 });

	//

	static int choice = 1;

	switch (choice)
	{
	case 1:
		config_snakeSpeed = 2.0f;
		break;
	case 2:
		config_snakeSpeed = 2.75f;
		break;
	case 3:
		config_snakeSpeed = 4.0f;
		break;
	case 4:
		config_snakeSpeed = 6.0f;
		break;
	case 5:
		config_snakeSpeed = 8.0f;
	}

	ImGui::Begin("Difficulty", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

	if (ImGui::RadioButton("Very slow", (choice == 1)))
		choice = 1;

	if (ImGui::RadioButton("Slow", (choice == 2)))
		choice = 2;

	if (ImGui::RadioButton("Medium", (choice == 3)))
		choice = 3;

	if (ImGui::RadioButton("Fast", (choice == 4)))
		choice = 4;

	if (ImGui::RadioButton("Very fast", (choice == 5)))
		choice = 5;


	if (ImGui::Button("Play"))
	{
		this->resetGame();
		isConfig = false;
	}
	
	if (ImGui::Button("Exit"))
		glfwSetWindowShouldClose(window, true);

	ImGui::End();
}

void Game::displayScore()
{
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize({ 120, 70 });

	//

	ImGui::Begin("Snake", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

		ImGui::Text("Score: %i", gameScore);
		ImGui::Text("Highscore: %i", gameHighscore);

	ImGui::End();
}

void Game::displayPause()
{
	ImGui::SetNextWindowPos({ 225, 75 });
	ImGui::SetNextWindowSize({ 150, 150 });

	//

	ImGui::Begin("Pause", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

	if (ImGui::Button("Continue"))
		isPaused = false;

	ImGui::SameLine();

	if (ImGui::Button("Exit"))
		glfwSetWindowShouldClose(window, true);

	if (ImGui::Button("Difficulty"))
	{
		isPaused = false;
		isConfig = true;
	}

	ImGui::End();
}

void Game::displayGameOver()
{
	ImGui::SetNextWindowPos({ 200, 230 });
	ImGui::SetNextWindowSize({ 200, 140 });
	
	//

	ImGui::Begin("Game over!", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

		ImGui::Text("Your score: %i", gameScore);

		if (ImGui::Button("Retry"))
			this->resetGame();

		ImGui::SameLine();

		if (ImGui::Button("Exit"))
			glfwSetWindowShouldClose(window, true);

		ImGui::SameLine();

		if (ImGui::Button("Difficulty"))
		{
			isPaused = false;
			isConfig = true;
		}

		ImGui::Spacing();

		if (ImGui::Button("Reset highscore") && ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
		{
			gameHighscore = 0;
			this->saveHighscore();
		}

		if (ImGui::IsItemHovered())
			ImGui::Text("Hold 'Left Ctrl' \nand click to proceed");

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

void Game::resetGame()
{
	delete snake;
	snake = new Snake(config_snakeSpeed);

	apple->moveToRandomPosition(snake->getBody());
}

void Game::saveHighscore()
{
	std::ofstream save("highscore", std::ios::binary);
	save.write((char*)&gameHighscore, sizeof(gameHighscore));
	save.close();
}

void Game::loadHighscore()
{
	std::ifstream load("highscore", std::ios::binary);
	load.read((char*)&gameHighscore, sizeof(gameHighscore));
	load.close();
}
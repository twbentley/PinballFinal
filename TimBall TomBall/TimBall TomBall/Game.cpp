#include "Game.h"

const int NUM_OBJECTS = 6;

Game::Game(void)
{
	// Initialize the GLFW libary
	if( glfwInit() != GL_TRUE )	// If returns GL_FALSE, initialize failed
		Shut_Down();

	// Open GLFW window with parameters
	if( glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, REDBITS, GREENBITS, BLUEBITS, ALPHABITS, DEPTHBITS, STENCILBITS, WINDOW_TYPE) != GL_TRUE )
		Shut_Down();

	// Initialize GLEW
	glewInit();

	// Set title of window
	glfwSetWindowTitle("DSA1 Project");

	// Reset the viewing matrix
	glLoadIdentity();

	// Instantiate Rendering and Updating
	Renderer = new Render();
	Updater = new Update();

	data = new Data_Container();

	shader = new ColorShader();

	Vector4 colorBlack = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	Vector4 colorRed = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
	Vector4 colorBlue = Vector4(0.0f, 0.0f, 1.0f, 0.0f);

	// Instantiate some game objects
	gameObjects["Ball1"] = new Ball(data->sprites["circle"], colorRed, -200.0f, 50.0f, 5.0f, -3.0f, 1.0f, 1.0f);
	//gameObjects["Ball2"] = new Ball(data->sprites["circle"], -200.0f, 75.0f, 1.0f, -3.5f);

	gameObjects["Bumper1"] = new Bumper(data->sprites["circle"], colorBlue, -190.0f, 150.0f, 1.0f, 1.0f);
	gameObjects["Bumper2"] = new Bumper(data->sprites["circle"], colorBlue, 130.0f, 150.0f, 1.0f, 1.0f);

	gameObjects["WallRight"] = new Wall(data->sprites["vert_rect"], colorBlack, 300.0f, 0.0f, 1.0f, 6.7f);
	gameObjects["WallLeft"] = new Wall(data->sprites["vert_rect"], colorBlack, -300.0f, 0.0f, 1.0f, 6.7f);
	gameObjects["WallTop"] = new Wall(data->sprites["horiz_rect"], colorBlack, 0.0f, 400.0f, 5.0f, 1.0f);
	gameObjects["WallBottom"] = new Wall(data->sprites["horiz_rect"], colorBlack, 0.0f, -400.0f, 5.0f, 1.0f);

	gameObjects["InnerWall1"] = new Flipper(data->sprites["flipper"], colorBlue, 260.0f, 370.0f, 135, 1.0f, 1.0f);
	gameObjects["InnerWall2"] = new Flipper(data->sprites["flipper"], colorBlue, 170.0f, -215.0f, 10, 1.0f, 1.0f);
	gameObjects["InnerWall3"] = new Flipper(data->sprites["flipper"], colorBlue, -230.0f, -215.0f, 170, 1.0f, 1.0f);
	gameObjects["InnerWall4"] = new Flipper(data->sprites["flipper"], colorBlue, 225.0f, -80.0f, 90, 5.0f, 1.0f);

	gameObjects["Flipper1"] = new Flipper(data->sprites["flipper"], colorBlue, -120.0f, -260.0f, 135, 1.0f, 1.0f);
	gameObjects["Flipper2"] = new Flipper(data->sprites["flipper"], colorBlue, 60.0f, -260.0f, 45, 1.0f, 1.0f);

	gameObjects["Spinner"] = new Spinner(data->sprites["flipper"], colorBlue, -30.0f, 250.0f, 1.0f, 1.0f);

	gameObjects["Spring"] = new Spring(data->sprites["spring"], colorBlue, 264.f, -390.0f, 1.0f, 1.0f);

	// Set the background color
	glClearColor(0.f, 1.f, 1.f, 0.f);

	// The program is running
	programRunning = true;

	// Setup the projection matrix. (Used to translate the 3d scene into the 2d viewport space
	float fieldOfView = (float)PI / 4.0f;
	float screenAspect = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	float screenNear = .1f;
	float screenDepth = 1000.0f;
	projectionMatrix = Matrix4::CreateProjectionMatrix(-WINDOW_WIDTH, WINDOW_WIDTH, -WINDOW_HEIGHT, WINDOW_HEIGHT, screenNear, screenDepth);
	
	gameState = "Menu";
}

Game::~Game(void)
{
	delete Renderer;
	delete Updater;
	delete data;
	delete shader;

	//gameObjects.clear();
	for(unordered_map<string, Game_Object*>::iterator itr = gameObjects.begin(); itr != gameObjects.end(); itr++)
		delete itr->second;
}

bool Game::Game_Loop()
{
	// Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render the current scene
	Renderer->Draw(gameState, shader, gameObjects, viewMatrix, projectionMatrix);

	// Swap front and back buffers
	glfwSwapBuffers(); 

	// Update game objects
	Updater->Update_Game(gameState, gameObjects);

	// Exit the program when ESC is pressed
	if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
		programRunning = false;
	// If the glfw window has been closed, shut down
	if( glfwGetWindowParam(GLFW_OPENED) == GL_FALSE )
		Shut_Down();

	return programRunning;
}

void Game::Shut_Down()
{
	glfwTerminate();
	exit(1);
}
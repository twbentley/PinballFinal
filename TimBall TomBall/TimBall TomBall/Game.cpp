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

	// Instantiate useful matrices
	viewMatrix = new Matrix4();
	projectionMatrix = new Matrix4();

	// Instantiate some game objects
	gameObjects["Ball"] = new Ball(data->sprites["circle"], 200.0f, 0.0f, -3.5f, -5.0f);
	gameObjects["OtherBall"] = new Ball(data->sprites["circle"], -200.0f, 75.0f, 1.0f, -3.5f);
	gameObjects["Bumper"] = new Game_Object(data->sprites["circle"], 0.0f, 0.0f);
	gameObjects["WallRight"] = new Game_Object(data->sprites["vert_rect"], 400.0f, 0.0f);
	gameObjects["WallLeft"] = new Game_Object(data->sprites["vert_rect"], -400.0f, 0.0f);
	gameObjects["WallTop"] = new Game_Object(data->sprites["horiz_rect"], 0.0f, 400.0f);
	gameObjects["WallBottom"] = new Game_Object(data->sprites["horiz_rect"], 0.0f, -400.0f);

	// Set the background color
	glClearColor(0.f, 1.f, 1.f, 1.f);

	// The program is running
	programRunning = true;

	// Setup the projection matrix. (Used to translate the 3d scene into the 2d viewport space
	float fieldOfView = (float)PI / 4.0f;
	float screenAspect = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	float screenNear = .1f;
	float screenDepth = 1000.0f;
	*projectionMatrix = Matrix4::CreateProjectionMatrix(-WINDOW_WIDTH, WINDOW_WIDTH, -WINDOW_HEIGHT, WINDOW_HEIGHT, screenNear, screenDepth);
}

Game::~Game(void)
{
}

bool Game::Game_Loop()
{
	// Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render the current scene
	Renderer->Draw(shader, gameObjects, viewMatrix, projectionMatrix);

	// Swap front and back buffers
	glfwSwapBuffers(); 

	// Update game objects
	Updater->Update_Game(gameObjects);

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
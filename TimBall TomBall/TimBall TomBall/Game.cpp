#include "Game.h"

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
	circle = new Game_Object(data->sprites["circle"], 0.0f, 0.0f);
	circle2 = new Game_Object(data->sprites["circle"], 0.5f, 0.0f);
	shader = new ColorShader();

	// Instantiate useful matrices
	viewMatrix = new Matrix4();
	projectionMatrix = new Matrix4();

	// Set the background color
	glClearColor(0.f, 1.f, 1.f, 1.f);

	// The program is running
	programRunning = true;
}

Game::~Game(void)
{
}

bool Game::Game_Loop()
{
	// Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render the current scene
	Renderer->Draw(shader, circle, circle2, viewMatrix, projectionMatrix);

	// Swap front and back buffers
	glfwSwapBuffers(); 

	// Update game objects
	Updater->Update_Game(circle);

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
#include "Game.h"

const int NUM_OBJECTS = 2;

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
	gameObjects = new Game_Object[NUM_OBJECTS];

	// Create a vertex array object
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

	data = new Data_Container();
	circle = new Game_Object(data->sprites["circle"], 200.0f, 0.0f);
	circle2 = new Game_Object(data->sprites["circle"], 0.0f, 0.0f);
	circle2->interactable = true;
	circle->interactable = false;

	shader = new ColorShader();

	// Instantiate useful matrices
	viewMatrix = new Matrix4[2];
	projectionMatrix = new Matrix4[2];

	// Set the background color
	glClearColor(0.f, 1.f, 1.f, 1.f);

	// The program is running
	programRunning = true;

	// Setup the projection matrix. (Used to translate the 3d scene into the 2d viewport space
	float fieldOfView = (float)PI / 4.0f;
	float screenAspect = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	float screenNear = .1f;
	float screenDepth = 1000.0f;
	*(projectionMatrix + 0) = Matrix4::CreateProjectionMatrix(-WINDOW_WIDTH, WINDOW_WIDTH, -WINDOW_HEIGHT, WINDOW_HEIGHT, screenNear, screenDepth);
	*(projectionMatrix + 1) = Matrix4::CreateProjectionMatrix(-WINDOW_WIDTH, WINDOW_WIDTH, -WINDOW_HEIGHT, WINDOW_HEIGHT, screenNear, screenDepth);
}

Game::~Game(void)
{
}

bool Game::Game_Loop()
{
	// Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render the current scene
	Renderer->Draw(shader, circle, *(viewMatrix + 0), *(projectionMatrix + 0));
	Renderer->Draw(shader, circle2, *(viewMatrix + 1), *(projectionMatrix + 1));

	// Swap front and back buffers
	glfwSwapBuffers(); 

	// Update game objects
	Updater->Update_Game(circle);
	//circle->ProcessCollisions(circle2);
	circle2->ProcessCollisions(circle);
	Updater->Update_Game(circle2);

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
// Author: Thomas Bentley
// Contributor: Timothy Reynolds

#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include "Render.h"
#include "Update.h"
#include "Game_Object.h"
#include "Data_Container.h"
#include "ColorShader.h"
#include "Bumper.h"
#include <GL/glfw.h>

using namespace std;

// Resolution of window
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 850;

// Number of bits per color (Color Depth)
const int REDBITS = 8;		// uses color depth of desktop if set to 0
const int GREENBITS = 8;	// Uses color depth closest to values specified
const int BLUEBITS = 8;		// 5,6,5 gives 16-bit color if OpenGL version supports it

// TODO: What do these mean?
const int ALPHABITS = 0;
const int DEPTHBITS = 8;
const int STENCILBITS = 0;

// Window type: WINDOW or FULLSCREEN
#define WINDOW_TYPE GLFW_WINDOW

// This class runs the pinball game
class Game
{
private: 
	bool programRunning;
	Render* Renderer;
	Update* Updater;
	unordered_map<string, Game_Object*> gameObjects;
	Data_Container* data;
	ColorShader* shader;
	string gameState;

	int ballCount;
	int score;
public:
	Game();
	~Game();

	bool Game_Loop();
	void Shut_Down();

	Matrix4 viewMatrix;
	Matrix4 projectionMatrix;
};

#endif
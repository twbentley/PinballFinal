#include "Game.h"

// Define for leak detection
#define _CRTDBG_MAP_ALLOC

// Prevent console window from opening
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int main()
{
	// Instantiate a game object
	Game* game = new Game();

	// Run the game loop
	while( (*game).Game_Loop() );

	// Clean up memory
	delete game;

	// Check for memory leaks
	_CrtDumpMemoryLeaks();
}
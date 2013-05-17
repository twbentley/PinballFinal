#include "Game.h"

// Define for leak detection
#define _CRTDBG_MAP_ALLOC

// Prevent console window from opening
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int main()
{
	Game* game = new Game();

	while( (*game).Game_Loop() );

	delete game;

	_CrtDumpMemoryLeaks();
}
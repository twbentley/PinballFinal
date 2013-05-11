#ifndef UPDATE_H
#define UPDATE_H

#include "Game_Object.h"
#include "Ball.h"
#include "Flipper.h"

// This class updates game objects (position, rotation, etc)
class Update
{
public:
	Update();
	~Update();

	void Update_Game(unordered_map<string, Game_Object*>);
};

#endif
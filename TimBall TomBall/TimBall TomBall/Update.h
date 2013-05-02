#ifndef UPDATE_H
#define UPDATE_H

#include "Game_Object.h"

// This class updates game objects (position, rotation, etc)
class Update
{
public:
	Update();
	~Update();

	void Update_Game(Game_Object*);
};

#endif
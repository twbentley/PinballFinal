// Author: Thomas Bentley
// Contributor: Timothy Reynolds

#ifndef UPDATE_H
#define UPDATE_H

#include "Game_Object.h"
#include "Ball.h"
#include "Flipper.h"
#include "Spring.h"
#include "Spinner.h"

// This class updates game objects (position, rotation, etc)
class Update
{
public:
	Update();
	~Update();

	void Update_Game(string&, unordered_map<string, Game_Object*>, int&, int&);
};

#endif
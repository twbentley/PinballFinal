#ifndef _WALL_H
#define _WALL_H

#include "Game_Object.h"

class Wall : public Game_Object
{
public:
	Wall(void);
	Wall(Polygon*, Vector4, float, float, float, float);
	~Wall(void);
};

#endif
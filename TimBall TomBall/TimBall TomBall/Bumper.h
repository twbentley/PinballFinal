#ifndef _BUMPER_H
#define _BUMPER_H

#include "Game_Object.h"

class Bumper : public Game_Object
{
public:
	Bumper(void);
	Bumper(Polygon*, float, float, float, float);
	~Bumper(void);
};

#endif
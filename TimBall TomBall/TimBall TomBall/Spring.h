#ifndef _SRING_H
#define _SRING_H

#include "Game_Object.h"

class Spring : public Game_Object
{
public:
	Spring(void);
	Spring(Polygon*, float, float, float, float);
	~Spring(void);

	void Update();
	
	bool started;
	bool returning;
	bool finished;
	int moveTimes;
	Vector4 startRadius;
};

#endif
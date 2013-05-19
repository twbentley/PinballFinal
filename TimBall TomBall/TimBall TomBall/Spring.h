// Author: Timothy Reynolds

#ifndef _SRING_H
#define _SRING_H

#include "Game_Object.h"

// This is a spring for launching the pinballs
class Spring : public Game_Object
{
public:
	Spring(void);
	Spring(Polygon*, Vector4, float, float, float, float);
	~Spring(void);

	void Update();
	
	bool started;
	bool returning;
	bool finished;
	int moveTimes;
	Vector4 startRadius;
};

#endif
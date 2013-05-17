#ifndef _BUMPER_H
#define _BUMPER_H

#include "Game_Object.h"

class Bumper : public Game_Object
{
public:
	Bumper(void);
	Bumper(Polygon*, Vector4, float, float, float, float);
	~Bumper(void);

	void Update(string);

	bool complete;
	bool shrinking;
	bool growing;
	int moveTimes;
	Vector4 startRadius;
};

#endif
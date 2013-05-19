// AUthor: Timothy Reynolds

#ifndef _BUMPER_H
#define _BUMPER_H

#include "Game_Object.h"

// Bumper object, bounces ball when hit, gives score
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
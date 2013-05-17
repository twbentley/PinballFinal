#ifndef FLIPPER_H
#define FLIPPER_H

#include "game_object.h"
class Flipper :
	public Game_Object
{
public:
	Flipper(void);
	Flipper(Polygon*, Vector4, float, float, int, float, float);
	~Flipper(void);

	void Update(string);

	bool flipped;
	bool moving;
	int moveTimes;
};

#endif
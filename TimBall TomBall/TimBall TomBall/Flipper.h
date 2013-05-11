#pragma once
#include "game_object.h"
class Flipper :
	public Game_Object
{
public:
	Flipper(void);
	Flipper(Polygon*, float, float);
	~Flipper(void);

	void Update();

	void PollUserInput();
};


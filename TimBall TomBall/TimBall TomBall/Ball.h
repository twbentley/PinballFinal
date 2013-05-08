#ifndef _BALL_H
#define _BALL_H

#include "Game_Object.h"

class Ball : public Game_Object
{
public:
	Ball();
	Ball(Polygon*, float, float);
	~Ball(void);

	Vector4* velocity;
	Vector4* accel;

	void Update(unordered_map<char*, Game_Object*>);

	void PollUserInput();
	void ProcessCollisions(unordered_map<char*, Game_Object*>);
};

#endif
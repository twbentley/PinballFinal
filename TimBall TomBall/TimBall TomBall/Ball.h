#ifndef _BALL_H
#define _BALL_H

#include "Game_Object.h"
#include "Wall.h"
#include "Spring.h"
#include "Spinner.h"
#include <cstdarg>

class Ball : public Game_Object
{
public:
	Ball();
	Ball(Polygon*, float, float, float, float, float, float);
	~Ball(void);

	Vector4* velocity;
	Vector4* accel;
	bool launched;

	void Update(unordered_map<string, Game_Object*>);

	void PollUserInput();
	void ProcessCollisions(unordered_map<string, Game_Object*>);
	void ApplyForce(unordered_map<string, Game_Object*>::iterator);
	bool FlipperCollision(Vector4&, Game_Object&,float&,bool&);
};

#endif
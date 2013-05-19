#ifndef _BALL_H
#define _BALL_H

#include "Game_Object.h"
#include "Wall.h"
#include "Spring.h"
#include "Spinner.h"
#include "Bumper.h"
#include "Flipper.h"
#include <cstdarg>

class Ball : public Game_Object
{
public:
	Ball();
	Ball(Polygon*, Vector4, float, float, float, float, float, float);
	~Ball(void);

	Vector4 velocity;
	Vector4 accel;
	bool launched;

	int Update(unordered_map<string, Game_Object*>, int&);

	int ProcessCollisions(unordered_map<string, Game_Object*>, int&);
	bool FlipperCollision(Vector4&, Game_Object&,float&,bool&);
};

#endif
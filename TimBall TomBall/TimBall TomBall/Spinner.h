#ifndef SPINNER_H
#define SPINNER_H

#include "Game_Object.h"
#include "Ball.h"

class Spinner :
	public Game_Object
{
public:
	Spinner(void);
	Spinner(Polygon*, Vector4, float, float, float, float);

	~Spinner(void);

	void Update();
	void Spin(float,Vector4, Game_Object*);
	void CheckSide(Game_Object* ball);

	float angle;
	float angularVelocity;
	bool isLeft;
	bool isTop;
};

#endif
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Polygon.h"
#include <string>

using namespace std;

// This class holds objects that will be in the game environment
class Game_Object
{
private:
	
public:
	Game_Object();
	Game_Object(Polygon*, float, float);
	~Game_Object();

	void Update();
	void Draw(ColorShader*, Matrix4*, Matrix4*);
	void PollUserInput();
	void ProcessCollisions(Game_Object*);

	Polygon* sprite;

	Matrix4* objectMatrix;

	Vector4* velocity;
	Vector4* accel;

	bool interactable;
};

#endif
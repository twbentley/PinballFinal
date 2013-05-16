#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Polygon.h"
#include <string>
#include <unordered_map>

using namespace std;

// This class holds objects that will be in the game environment
class Game_Object
{
private:
	
public:
	Game_Object();
	Game_Object(Polygon*, float, float, float, float);
	~Game_Object();
	
	void Draw(ColorShader*, Matrix4*, Matrix4*);

	void UpdateObjectMatrix();
	Vector4 GetRadius();

	Polygon* sprite;
	Matrix4 objectMatrix;
	Matrix4 translationMatrix;
	Matrix4 rotationMatrix;
	Matrix4 scaleMatrix;
	Vector4 radius;
};

#endif
// Author: Thomas Bentley & Timothy Reynolds

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Polygon.h"
#include <string>
#include <unordered_map>

using namespace std;

// This class is a game object that will be in the game environment
class Game_Object
{
private:
	
public:
	Game_Object();
	Game_Object(Polygon*, Vector4, float, float, float, float);
	~Game_Object();
	
	void Draw(ColorShader*, Matrix4, Matrix4);

	void UpdateObjectMatrix();
	Vector4 GetRadius();

	Polygon* sprite;
	Matrix4 objectMatrix;
	Matrix4 translationMatrix;
	Matrix4 rotationMatrix;
	Matrix4 scaleMatrix;
	Vector4 radius;
	Vector4 objectsColor;
	float initialTime;
	float finalTime;
};

#endif
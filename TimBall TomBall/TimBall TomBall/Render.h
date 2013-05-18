#ifndef RENDER_H
#define RENDER_H

#include <sstream>
#include "Polygon.h"
#include "Game_Object.h"

// This class renders objects
class Render
{
public:
	Render();
	~Render();

	void Draw(string gameState, ColorShader*, unordered_map<string, Game_Object*>, Matrix4, Matrix4, int, int);
	void DrawBitmapText(string, float, float, float);
};

#endif
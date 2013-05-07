#ifndef RENDER_H
#define RENDER_H

#include "Polygon.h"
#include "Game_Object.h"

// This class renders objects
class Render
{
public:
	Render();
	~Render();

	void Draw(ColorShader*, unordered_map<char*, Game_Object*>, Matrix4*, Matrix4*);
};

#endif
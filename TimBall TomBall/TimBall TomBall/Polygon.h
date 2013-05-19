// Author: Timothy Reynolds
// Contributor: Thomas Bentley

#ifndef POLYGON_H
#define POLYGON_H

#include "Vector4.h"
#include "Matrix4.h"
#include "ColorShader.h"
#include "FileIO.h"

// Define value of pi
#define PI 3.14159265358979323846264338327950288

// Class representing visual representation of game objects
class Polygon
{
private:
	GLuint vertexBuffer;
	GLuint indexbuffer;
	Vector4* vertices;
	unsigned int* indices;
	int numIndices;
	Vector4 radius;
	GLuint vao;
public:
	Polygon();
	Polygon(string);
	~Polygon(void);

	//ColorShader* shader;
	void Draw(ColorShader*, Matrix4, Matrix4, Matrix4, Vector4);
	
	Vector4 GetRadius();
};

#endif
#ifndef POLYGON_H
#define POLYGON_H

#include "Vector4.h"
#include "Matrix4.h"
#include "ColorShader.h"

// Define value of pi
#define PI 3.14159265358979323846264338327950288

class Polygon
{
private:
	GLuint buffer;
	GLuint vao;
	Vector4* points;
	int num_sides;
	GLfloat radius;
public:
	Polygon();
	~Polygon(void);

	//ColorShader* shader;
	void Draw(ColorShader*, Matrix4*, Matrix4*, Matrix4*);
};

#endif
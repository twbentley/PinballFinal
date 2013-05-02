#ifndef COLORSHADER_H
#define COLORSHADER_H

#include "Vector2.h"
#include "Matrix4.h"
#include <fstream>
#include <vector>

// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

// This class renders objects
class ColorShader
{
public:
	ColorShader();
	~ColorShader();

	GLuint shaderProgram;
	char* readShaderSource(const char* shaderFile);
	GLuint InitShader(const char* vShaderFile, const char* fShaderFile);

	void Render(Matrix4*, Matrix4*, Matrix4*, int);
	void SetShader();
	void SetShaderParameters(Matrix4*, Matrix4*, Matrix4*);
};

#endif
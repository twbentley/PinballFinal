// Author: Angel
// Contributors: Thomas Bentley, Timothy Reynolds
// Modified from Angel's InitShader class. Streamlined, organized, and added to.

#ifndef COLORSHADER_H
#define COLORSHADER_H

#include "Vector2.h"
#include "Matrix4.h"
#include <fstream>
#include <vector>

// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

// This is a shader class for rendering objects
class ColorShader
{
public:
	ColorShader();
	~ColorShader();

	GLuint shaderProgram;
	char* readShaderSource(const char* shaderFile);
	GLuint InitShader(const char* vShaderFile, const char* fShaderFile);

	void Render(Matrix4*, Matrix4*, Matrix4*, int, Vector4);
	void SetShader();
	void SetShaderParameters(Matrix4*, Matrix4*, Matrix4*, Vector4);
};

#endif
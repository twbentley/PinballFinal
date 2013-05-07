#include "Render.h"

Render::Render(void)
{
}

Render::~Render(void)
{
}

// Draw the whole scene
void Render::Draw(ColorShader* shader, Game_Object* object, Matrix4 viewMatrix, Matrix4 projectionMatrix)
{
	// Reset the viewing matrix
	glLoadIdentity();

	//object->Draw(shader, viewMatrix, projectionMatrix);
	object->Draw(shader, &viewMatrix, &projectionMatrix);
}
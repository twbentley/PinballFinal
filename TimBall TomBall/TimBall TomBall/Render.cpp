#include "Render.h"

Render::Render(void)
{
}

Render::~Render(void)
{
}

// Draw the whole scene
void Render::Draw(ColorShader* shader, Game_Object* object, Game_Object* object2, Matrix4* viewMatrix, Matrix4* projectionMatrix)
{
	// Reset the viewing matrix
	glLoadIdentity();

	//object->Draw(shader, viewMatrix, projectionMatrix);
	object2->Draw(shader, viewMatrix, projectionMatrix);
}
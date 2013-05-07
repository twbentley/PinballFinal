#include "Render.h"

Render::Render(void)
{
}

Render::~Render(void)
{
}

// Draw the whole scene
void Render::Draw(ColorShader* shader, unordered_map<char*, Game_Object*> objects, Matrix4* viewMatrix, Matrix4* projectionMatrix)
{
	// Reset the viewing matrix
	glLoadIdentity();

	//object->Draw(shader, viewMatrix, projectionMatrix);
	//objects->Draw(shader, &viewMatrix, &projectionMatrix);

	for(unordered_map<char*, Game_Object*>::iterator itr = objects.begin(); itr != objects.end(); itr++)
	{
		(*itr).second->Draw(shader, viewMatrix, projectionMatrix);
	}
}
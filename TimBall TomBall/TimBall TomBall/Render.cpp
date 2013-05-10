#include "Render.h"

Render::Render(void)
{
}

Render::~Render(void)
{
}

// Draw the whole scene
void Render::Draw(ColorShader* shader, unordered_map<string, Game_Object*> objects, Matrix4* viewMatrix, Matrix4* projectionMatrix)
{
	// Reset the viewing matrix
	//glLoadIdentity();

	glEnableClientState(GL_VERTEX_ARRAY);

	for(auto itr = objects.begin(); itr != objects.end(); itr++)
	{
		itr->second->Draw(shader, viewMatrix, projectionMatrix);
	}

	glDisableClientState(GL_VERTEX_ARRAY);
}
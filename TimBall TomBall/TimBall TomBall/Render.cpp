#include "Render.h"
#include <GL/glut.h>

Render::Render(void)
{
}

Render::~Render(void)
{
}

// Draw the whole scene
void Render::Draw(string gameState, ColorShader* shader, unordered_map<string, Game_Object*> objects, Matrix4 viewMatrix, Matrix4 projectionMatrix)
{
	// Reset the viewing matrix
	//glLoadIdentity();

	glEnableClientState(GL_VERTEX_ARRAY);

	if(gameState == "Menu")
	{
		float temp = -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Timball Tomball") / 600.0f;		
		DrawBitmapText("Timball Tomball", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Timball Tomball") / 600.0f, 0.5f, 0.0f);
		DrawBitmapText("By: Timothy and Tommy", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"By: Timothy and Tommy") / 600.0f, 0.4f, 0.0f);
		DrawBitmapText("Instructions:", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Instructions:") / 600.0f, 0.2f, 0.0f);
		DrawBitmapText("-Get as high a score as", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"-Get as high a score as") / 600.0f, 0.1f, 0.0f);
		DrawBitmapText("possible with three balls.", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"possible with three balls.") / 600.0f, 0.0f, 0.0f);
		DrawBitmapText("-Use A and E keys to flip paddle.", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"-Use A and E keys to flip paddle.") / 600.0f, -0.1f, 0.0f);
		DrawBitmapText("-Use spacebar to shoot ball.", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"-Use spacebar to shoot ball.") / 600.0f, -0.2f, 0.0f);
		DrawBitmapText("Press enter to start.", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Press enter to start.") / 600.0f, -0.4f, 0.0f);
	}
	else
	{
		for(auto itr = objects.begin(); itr != objects.end(); itr++)
		{
			itr->second->Draw(shader, viewMatrix, projectionMatrix);
		}
	}

	glDisableClientState(GL_VERTEX_ARRAY);
}

void Render::DrawBitmapText(string stringToRender, float x, float y, float z) 
{  
	glScalef(1.0f, 1.0f, 1.0f);
	glRasterPos3f(x, y, z);
	
	glColor3f(0.0f, 0.0f, 0.0f);
	
	for (int i = 0; i < stringToRender.length(); i++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, stringToRender[i]);
	}
}
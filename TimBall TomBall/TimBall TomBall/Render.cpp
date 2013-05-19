#include "Render.h"
#include <GL/glut.h>

Render::Render(void)
{
}

Render::~Render(void)
{
}

// Draw the whole scene
void Render::Draw(string gameState, ColorShader* shader, unordered_map<string, Game_Object*> objects, Matrix4 viewMatrix, Matrix4 projectionMatrix, int ballCount, int score)
{
	// Reset the viewing matrix
	//glLoadIdentity();

	glEnableClientState(GL_VERTEX_ARRAY);

	if(gameState == "Menu")
	{
		DrawBitmapText("Timball Tomball", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Timball Tomball") / 600.0f, 0.5f, 0.0f);
		DrawBitmapText("Instructions:", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Instructions:") / 600.0f, 0.2f, 0.0f);
		DrawBitmapText("-Get as high a score as", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"-Get as high a score as") / 600.0f, 0.1f, 0.0f);
		DrawBitmapText("possible with three balls.", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"possible with three balls.") / 600.0f, 0.0f, 0.0f);
		DrawBitmapText("-Use A and D keys to flip paddle.", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"-Use A and E keys to flip paddle.") / 600.0f, -0.1f, 0.0f);
		DrawBitmapText("-Use spacebar to shoot ball.", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"-Use spacebar to shoot ball.") / 600.0f, -0.2f, 0.0f);
		DrawBitmapText("Press enter to start.", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Press enter to start.") / 600.0f, -0.4f, 0.0f);
	}
	else if(gameState == "Credits")
	{
		DrawBitmapText("Credits:", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Credits:") / 600.0f, 0.4f, 0.0f);
		DrawBitmapText("Creators: Timothy Reynolds, Tommy Bentley", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Creators: Timothy Reynolds, Tommy Bentley") / 600.0f, 0.2f, 0.0f);
		DrawBitmapText("Book: Interactive Computer Graphics by Angel", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Book: Interactive Computer Graphics by Angel") / 600.0f, 0.1f, 0.0f);
		DrawBitmapText("Source: Matrices, Geekyblogger.com", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Source: Matrices, Geekyblogger.com") / 600.0f, 0.0f, 0.0f);

		DrawBitmapText("Press enter to restart.", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Press enter to restart.") / 600.0f, -0.3f, 0.0f);
	}
	else if(gameState == "Game" || gameState == "Paused")
	{
		for(auto itr = objects.begin(); itr != objects.end(); itr++)
		{
			itr->second->Draw(shader, viewMatrix, projectionMatrix);
		}

		DrawBitmapText("Timball Tomball", -0.95f, -0.97f, 0.0f);
		stringstream ss;
		ss << "Score: " << score;
		DrawBitmapText(ss.str(), 0.4f, -0.97f, 0.0f);
		ss.str("");
		ss << "Balls remaining: " << ballCount;
		DrawBitmapText(ss.str(), -0.3f, -0.97f, 0.0f);	
	}

	if(gameState == "Paused")
	{
		DrawBitmapText("Paused", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Paused") / 600.0f, 0.0f, 0.0f);
		DrawBitmapText("Press enter to resume.", -glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Press enter to resume.") / 600.0f, -0.1f, 0.0f);
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
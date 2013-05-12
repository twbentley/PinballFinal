#include "Game_Object.h"

Game_Object::Game_Object() : objectMatrix(), /*rotationMatrix(), scaleMatrix(), */translationMatrix()
{
	
}

Game_Object::Game_Object(Polygon* sprite_name, float positionX, float positionY)
{
	sprite = sprite_name;
	translationMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
	//objectMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
}

Game_Object::~Game_Object()
{
}

void Game_Object::Draw(ColorShader* shader, Matrix4* viewMatrix, Matrix4* projectionMatrix)
{
	UpdateObjectMatrix();
	sprite->Draw(shader, &objectMatrix, viewMatrix, projectionMatrix);
}

void Game_Object::UpdateObjectMatrix()
{
	(objectMatrix) = /*(rotationMatrix) * (scaleMatrix) * */(translationMatrix);
}
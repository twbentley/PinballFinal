#include "Game_Object.h"

Game_Object::Game_Object()
{
}

Game_Object::Game_Object(Polygon* sprite_name, float positionX, float positionY)
{
	sprite = sprite_name;
	objectMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
}

Game_Object::~Game_Object()
{
}

void Game_Object::Draw(ColorShader* shader, Matrix4* viewMatrix, Matrix4* projectionMatrix)
{
	sprite->Draw(shader, objectMatrix, viewMatrix, projectionMatrix);
}


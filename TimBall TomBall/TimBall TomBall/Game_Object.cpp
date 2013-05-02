#include "Game_Object.h"


Game_Object::Game_Object()
{
}

Game_Object::Game_Object(Polygon* sprite_name, float positionX, float positionY)
{
	sprite = sprite_name;
	objectMatrix = new Matrix4();
	velocity = new Vector2(0.0, 0.0f);
	accel = new Vector2(0.0f, 0.0f);
}

Game_Object::~Game_Object()
{
}

void Game_Object::Update()
{
	//*position += *velocity;
	//*velocity += *accel;
	//*testObject->accel -= Vector2(0.1f, 0.0f);
}

void Game_Object::Draw(ColorShader* shader, Matrix4* viewMatrix, Matrix4* projectionMatrix)
{
	sprite->Draw(shader, objectMatrix, viewMatrix, projectionMatrix);
}
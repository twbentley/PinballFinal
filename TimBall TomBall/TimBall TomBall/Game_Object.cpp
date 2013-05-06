#include "Game_Object.h"


Game_Object::Game_Object()
{
}

Game_Object::Game_Object(Polygon* sprite_name, float positionX, float positionY)
{
	sprite = sprite_name;
	objectMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
	velocity = new Vector4(5.0f, 0.0f, 0.0f, 0.0f);
	accel = new Vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

Game_Object::~Game_Object()
{
}

void Game_Object::Update()
{
	//*position += *velocity;
	//*testObject->accel -= Vector2(0.1f, 0.0f);
	//objectMatrix = Matrix4::UpdatePositionMatrix(objectMatrix, velocity.x, velocity.y, 0);
	Matrix4::UpdatePositionMatrix(*objectMatrix, velocity->x, velocity->y, 0);
	*velocity += *accel;

	// "Friction"
	//if(accel > 0)
	//	*(accel) += Vector4(-0.01f, 0.0f, 0.0f, 0);
	//else if(accel < 0)
	//	*(accel) += Vector4(0.01f, 0.0f, 0.0f, 0);
}

void Game_Object::Draw(ColorShader* shader, Matrix4* viewMatrix, Matrix4* projectionMatrix)
{
	sprite->Draw(shader, objectMatrix, viewMatrix, projectionMatrix);
}
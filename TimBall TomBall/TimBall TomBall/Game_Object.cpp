#include "Game_Object.h"

Game_Object::Game_Object()
{
}

Game_Object::Game_Object(Polygon* sprite_name, float positionX, float positionY, float scaleX, float scaleY)
{
	sprite = sprite_name;
	translationMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
	Matrix4::UpdateScaleMatrix(scaleMatrix, scaleX, scaleY, 1.0f);

	radius = sprite_name->GetRadius() * Vector4(scaleX, scaleY, 1.0f, 1.0f);
}

Game_Object::~Game_Object()
{
	delete sprite;
}

void Game_Object::Draw(ColorShader* shader, Matrix4 viewMatrix, Matrix4 projectionMatrix)
{
	UpdateObjectMatrix();
	sprite->Draw(shader, objectMatrix, viewMatrix, projectionMatrix);
}

void Game_Object::UpdateObjectMatrix()
{
	objectMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

Vector4 Game_Object::GetRadius()
{ 
	return radius; 
}
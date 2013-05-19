#include "Game_Object.h"

// Default constructor
Game_Object::Game_Object() { }

// Parameterized constructor
Game_Object::Game_Object(Polygon* sprite_name, Vector4 color, float positionX, float positionY, float scaleX, float scaleY)
{
	// Set the sprite
	sprite = sprite_name;

	// Set object to its specified position and scale
	translationMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
	Matrix4::UpdateScaleMatrix(scaleMatrix, scaleX, scaleY, 1.0f);

	// Get the radius of the object and its color
	radius = sprite_name->GetRadius() * Vector4(scaleX, scaleY, 1.0f, 1.0f);
	objectsColor = color;
}

// Destructor
Game_Object::~Game_Object() { }

// Draw a game object and update the object mesh
void Game_Object::Draw(ColorShader* shader, Matrix4 viewMatrix, Matrix4 projectionMatrix)
{
	UpdateObjectMatrix();
	sprite->Draw(shader, objectMatrix, viewMatrix, projectionMatrix, objectsColor);
}

// Update the object matrix (object mesh) based on its translation, rotation, and scale
void Game_Object::UpdateObjectMatrix()
{
	objectMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

// Getter for the radius of the game object
Vector4 Game_Object::GetRadius()
{ 
	return radius; 
}
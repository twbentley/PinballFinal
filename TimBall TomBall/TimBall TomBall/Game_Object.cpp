#include "Game_Object.h"

Game_Object::Game_Object()
{
	interactable = false;
}

Game_Object::Game_Object(Polygon* sprite_name, float positionX, float positionY)
{
	sprite = sprite_name;
	objectMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
	velocity = new Vector4(0.0f, 0.0f, 0.0f, 0.0f);
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

	if(interactable)
		PollUserInput();
}

void Game_Object::Draw(ColorShader* shader, Matrix4* viewMatrix, Matrix4* projectionMatrix)
{
	sprite->Draw(shader, objectMatrix, viewMatrix, projectionMatrix);
}

// Get user input for various purposes
void Game_Object::PollUserInput()
{
	// Horizontal Keyboard-based input
	if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		Matrix4::UpdatePositionMatrix(*objectMatrix, 5, 0, 0);
	}
	else if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		Matrix4::UpdatePositionMatrix(*objectMatrix, -5, 0, 0);
	}
	
	// Horizontal Keyboard-based input
	if(glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS)
	{
		Matrix4::UpdatePositionMatrix(*objectMatrix, 0, 5, 0);
	}
	else if(glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		Matrix4::UpdatePositionMatrix(*objectMatrix, 0, -5, 0);
	}
}

void Game_Object::ProcessCollisions(Game_Object* other)
{
	// Calculate useful values
	Vector2 thisCenter(this->objectMatrix->matrix[0][3], this->objectMatrix->matrix[1][3]);
	Vector2 otherCenter(other->objectMatrix->matrix[0][3], other->objectMatrix->matrix[1][3]);
	GLfloat combinedRadius = this->sprite->GetRadius() + other->sprite->GetRadius();

	// Detect spherical collision
	if( ( (thisCenter.x - otherCenter.x) * (thisCenter.x - otherCenter.x) ) +
		( (thisCenter.y - otherCenter.y) * (thisCenter.y - otherCenter.y) ) <
		( combinedRadius * combinedRadius) )
	{
		// Do something
		// acc -> vel -> pos
		// TODO: World bounds, objects move via force (schwartz's Circle-Circle)
	}
}
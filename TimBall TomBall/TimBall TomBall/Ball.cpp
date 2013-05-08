#include "Ball.h"

Ball::Ball()
{
}

Ball::Ball(Polygon* sprite_name, float positionX, float positionY)
{
	sprite = sprite_name;
	objectMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
	velocity = new Vector4(0.0f, -5.0f, 0.0f, 0.0f);
	accel = new Vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

Ball::~Ball(void)
{
}

void Ball::Update(unordered_map<char*, Game_Object*> objects)
{
	Matrix4::UpdatePositionMatrix(*objectMatrix, velocity->x, velocity->y, 0);
	*velocity += *accel;

	// "Friction"
	//if(accel > 0)
	//	*(accel) += Vector4(-0.01f, 0.0f, 0.0f, 0);
	//else if(accel < 0)
	//	*(accel) += Vector4(0.01f, 0.0f, 0.0f, 0);

	PollUserInput();
	ProcessCollisions(objects);
}

// Get user input for various purposes
void Ball::PollUserInput()
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

void Ball::ProcessCollisions(unordered_map<char*, Game_Object*> objects)
{
	// Calculate 
	Vector2 thisCenter(this->objectMatrix->matrix[0][3], this->objectMatrix->matrix[1][3]);

	// Check collision with all objects
	for(unordered_map<char*, Game_Object*>::iterator itr = objects.begin(); itr != objects.end(); itr++)
	{
		Vector2 otherCenter(itr->second->objectMatrix->matrix[0][3], itr->second->objectMatrix->matrix[1][3]);
		Vector4 combinedRadius = this->sprite->GetRadius() + itr->second->sprite->GetRadius();

		// TODO::If check for appropriate type of object, Check based on dictionary name
		if(itr->first == "WallLeft" && thisCenter.x - sprite->GetRadius().x < otherCenter.x + itr->second->sprite->GetRadius().x)
		{
			velocity = new Vector4(velocity->x * -1, 0.0f, 0.0f, 0.0f);
		}
		if(itr->first == "WallRight" && thisCenter.x + sprite->GetRadius().x > otherCenter.x - itr->second->sprite->GetRadius().x)
		{
			velocity = new Vector4(velocity->x * -1, 0.0f, 0.0f, 0.0f);
		}
		if(itr->first == "WallTop" && thisCenter.y + sprite->GetRadius().x > otherCenter.y - itr->second->sprite->GetRadius().y)
		{
			velocity = new Vector4(0.0f, velocity->y * -1, 0.0f, 0.0f);
		}
		if(itr->first == "WallBottom" && thisCenter.y - sprite->GetRadius().x < otherCenter.y + itr->second->sprite->GetRadius().y)
		{
			velocity = new Vector4(0.0f, velocity->y * -1, 0.0f, 0.0f);
		}

		// Detect spherical collision
		if( ( (thisCenter.x - otherCenter.x) * (thisCenter.x - otherCenter.x) ) +
			( (thisCenter.y - otherCenter.y) * (thisCenter.y - otherCenter.y) ) <
			( combinedRadius.x * combinedRadius.x) )
		{
			// Do something
			// acc -> vel -> pos
			// TODO: World bounds, objects move via force (schwartz's Circle-Circle)
		}
	}
}

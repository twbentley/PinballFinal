#include "Ball.h"

Ball::Ball()
{
}

Ball::Ball(Polygon* sprite_name, float positionX, float positionY, float velX, float velY)
{
	sprite = sprite_name;
	objectMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
	velocity = new Vector4(velX, velY, 0.0f, 0.0f);
	accel = new Vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

Ball::~Ball(void)
{
}

void Ball::Update(unordered_map<string, Game_Object*> objects)
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

void Ball::ProcessCollisions(unordered_map<string, Game_Object*> objects)
{
	// Calculate 
	Vector2 thisCenter(this->objectMatrix->matrix[0][3], this->objectMatrix->matrix[1][3]);

	// Check collision with all objects
	for(unordered_map<string, Game_Object*>::iterator itr = objects.begin(); itr != objects.end(); itr++)
	{
		Vector2 otherCenter(itr->second->objectMatrix->matrix[0][3], itr->second->objectMatrix->matrix[1][3]);
		Vector4 combinedRadius = this->sprite->GetRadius() + itr->second->sprite->GetRadius();

		// Check for collidable objects, based on dictionary name
		if(itr->first == "WallLeft" && thisCenter.x - sprite->GetRadius().x < otherCenter.x + itr->second->sprite->GetRadius().x)
		{
			velocity->x += this->velocity->x * -2.0f;
		}
		if(itr->first == "WallRight" && thisCenter.x + sprite->GetRadius().x > otherCenter.x - itr->second->sprite->GetRadius().x)
		{
			velocity->x += this->velocity->x * -2.0f;
		}
		if(itr->first == "WallTop" && thisCenter.y + sprite->GetRadius().x > otherCenter.y - itr->second->sprite->GetRadius().y)
		{
			velocity->y += this->velocity->y * -2.0f;
		}
		if(itr->first == "WallBottom" && thisCenter.y - sprite->GetRadius().x < otherCenter.y + itr->second->sprite->GetRadius().y)
		{
			velocity->y += this->velocity->y * -2.0f;
		}


		// Detect spherical collision
		if( ( itr->first.find("Ball") != string::npos || itr->first == "Bumper" || itr->first == "Flipper1") && 
			itr->second != this && 
			( (thisCenter.x - otherCenter.x) * (thisCenter.x - otherCenter.x) ) +
			( (thisCenter.y - otherCenter.y) * (thisCenter.y - otherCenter.y) ) <
			( combinedRadius.x * combinedRadius.x) )
		{
			// Get the vector in between the two objects
			Vector4 hyp( (thisCenter.x - otherCenter.x), (thisCenter.y - otherCenter.y), 0.0f, 0.0f );
			// Get the normal vector to the colliding object
			Vector4 normal(hyp.normalize(hyp));
			// Calculate a new velocity
			*velocity = normal * (velocity->dot(normal) * -2.0f) + *velocity;
			// Separate collided objects (upon collision 2 objects will slightly overlap so this is necessary)
			Matrix4::UpdatePositionMatrix(*objectMatrix, velocity->x, velocity->y, 0);

			// NOTE: Ball-Ball collision sometimes only changes the velocity of one of the balls
		}
	}
}

// Apply a force to the object (DEPRECATED)
void Ball::ApplyForce(unordered_map<string, Game_Object*>::iterator other)
{
	//Vector4& tmp = *velocity;
	//Vector4 thisForce( tmp );	// velocity / mass
	//Vector4 otherForce;
	//Vector4 thisFinalForce;
	//Vector4 otherFinalForce;

	//if(other->first == "Circle")
	//{
	//	otherForce = *( static_cast<Ball*>(other->second)->velocity );
	//}
	//else
	//{	}

	//// You'll want to replace all the 1's with something later, this is the general setup.
	//thisFinalForce = thisForce * (1.0f - 1.0f) / (1.0f + 1.0f) + otherForce * (2.0f * 1.0f / (1.0f + 1.0f));
	//otherFinalForce = otherForce * (1.0f - 1.0f) / (1.0f + 1.0f) + thisForce * (2.0f * 1.0f / (1.0f + 1.0f));
	///*thisFinalForce /= mass;
	//otherFinalForce /= other->mass;*/

	//accel->x = thisFinalForce.x;
	//accel->y = thisFinalForce.y;
	//accel->z = zForce;
	//accel->w = wForce;
}
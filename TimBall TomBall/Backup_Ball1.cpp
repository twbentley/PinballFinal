#include "Ball.h"

Ball::Ball()
{
}

Ball::Ball(Polygon* sprite_name, float positionX, float positionY, float velX, float velY)
{
	sprite = sprite_name;
	translationMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
	//objectMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);

	velocity = new Vector4(velX, velY, 0.0f, 0.0f);
	accel = new Vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

Ball::~Ball(void)
{
}

void Ball::Update(unordered_map<string, Game_Object*> objects)
{
	Matrix4::UpdatePositionMatrix(translationMatrix, velocity->x, velocity->y, 0);
	*velocity += *accel;

	// "Friction"
	//if(accel > 0)
	//	*(accel) += Vector4(-0.01f, 0.0f, 0.0f, 0);
	//else if(accel < 0)
	//	*(accel) += Vector4(0.01f, 0.0f, 0.0f, 0);

	//PollUserInput();
	ProcessCollisions(objects);
}

// Get user input for various purposes
void Ball::PollUserInput()
{
	// Horizontal Keyboard-based input
	//if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
	//{
	//	Matrix4::UpdatePositionMatrix(translationMatrix, 5, 0, 0);
	//}
	//else if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
	//{
	//	Matrix4::UpdatePositionMatrix(translationMatrix, -5, 0, 0);
	//}

	//// Horizontal Keyboard-based input
	//if(glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS)
	//{
	//	Matrix4::UpdatePositionMatrix(translationMatrix, 0, 5, 0);
	//}
	//else if(glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS)
	//{
	//	Matrix4::UpdatePositionMatrix(translationMatrix, 0, -5, 0);
	//}
}

void Ball::ProcessCollisions(unordered_map<string, Game_Object*> objects)
{
	// Calculate 
	Vector4 thisCenter(this->translationMatrix[0][3], this->translationMatrix[1][3], 0.0f, 0.0f);

	// Check collision with all objects
	for(unordered_map<string, Game_Object*>::iterator itr = objects.begin(); itr != objects.end(); itr++)
	{
		//
		Vector4 otherCenter(itr->second->translationMatrix[0][3], itr->second->translationMatrix[1][3], 0.0f, 0.0f);
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
		if( ( itr->first.find("Ball") != string::npos || itr->first == "Bumper" /*|| itr->first == "Flipper1"*/) && 
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
			Matrix4::UpdatePositionMatrix(translationMatrix, velocity->x, velocity->y, 0);

			// NOTE: Ball-Ball collision sometimes only changes the velocity of one of the balls
		}

		if(itr->first == "Flipper1" && FlipperCollision(otherCenter, *(itr->second)))
		{
			Vector4 flipperRadius(itr->second->sprite->GetRadius().x, itr->second->sprite->GetRadius().y, 0.0f, 0.0f);
			GLfloat cosAngle(itr->second->rotationMatrix[0][0]);
			GLfloat sinAngle(-itr->second->rotationMatrix[0][1]);
			//GLfloat hitAngle = atan2(velocity->y,velocity->x);

			// Get the vector in between the two objects
			Vector4 hyp;

			if(cosAngle > 0 && cosAngle > 0)
			{
				if( (thisCenter.x < otherCenter.x - cosAngle*flipperRadius.x) && ( thisCenter.y < otherCenter.y - sinAngle*flipperRadius.y) )
				{
					// Odd Case
					if( (velocity->x < 0 && velocity->y < 0) || (velocity->x < 0 && velocity->y > 0) )
						hyp = Vector4(  sinAngle * ( (otherCenter.x - flipperRadius.x + flipperRadius.y) - thisCenter.x ), cosAngle * (otherCenter.y - thisCenter.y), 0.0f, 0.0f );
					// Normal case
					else
						hyp = Vector4(  cosAngle * ( (otherCenter.x - flipperRadius.x + flipperRadius.y) - thisCenter.x ), sinAngle * (otherCenter.y - thisCenter.y), 0.0f, 0.0f );
				}
				else if( (thisCenter.x > otherCenter.x + cosAngle*flipperRadius.x) && (thisCenter.y > otherCenter.y + sinAngle*flipperRadius.y) )
				{
					// Odd case
					if( (velocity->x > 0 && velocity->y > 0) || (velocity->x > 0 && velocity->y < 0) )
						hyp = Vector4( sinAngle * ( (otherCenter.x + flipperRadius.x - flipperRadius.y) - thisCenter.x ) , cosAngle * (otherCenter.y - thisCenter.y), 0.0f, 0.0f );
					// Normal case
					else
						hyp = Vector4( cosAngle * ( (otherCenter.x + flipperRadius.x - flipperRadius.y) - thisCenter.x ) , sinAngle * (otherCenter.y - thisCenter.y), 0.0f, 0.0f );
				}
				else
					hyp = Vector4( sinAngle * (otherCenter.x - thisCenter.x), cosAngle * (otherCenter.y - thisCenter.y), 0.0f, 0.0f );
			}
			else
			{
				if( (thisCenter.x < otherCenter.x - cosAngle*flipperRadius.x) || ( thisCenter.y < otherCenter.y - sinAngle*flipperRadius.y) )
				{
					// Odd Case
					if( (velocity->x < 0 && velocity->y < 0) || (velocity->x < 0 && velocity->y > 0) )
						hyp = Vector4(  sinAngle * ( (otherCenter.x - flipperRadius.x + flipperRadius.y) - thisCenter.x ), cosAngle * (otherCenter.y - thisCenter.y), 0.0f, 0.0f );
					// Normal case
					else
						hyp = Vector4(  cosAngle * ( (otherCenter.x - flipperRadius.x + flipperRadius.y) - thisCenter.x ), sinAngle * (otherCenter.y - thisCenter.y), 0.0f, 0.0f );
				}
				else if( (thisCenter.x > otherCenter.x + cosAngle*flipperRadius.x) || (thisCenter.y > otherCenter.y + sinAngle*flipperRadius.y) )
				{
					// Odd case
					if( (velocity->x > 0 && velocity->y > 0) || (velocity->x > 0 && velocity->y < 0) )
						hyp = Vector4( sinAngle * ( (otherCenter.x + flipperRadius.x - flipperRadius.y) - thisCenter.x ) , cosAngle * (otherCenter.y - thisCenter.y), 0.0f, 0.0f );
					// Normal case
					else
						hyp = Vector4( cosAngle * ( (otherCenter.x + flipperRadius.x - flipperRadius.y) - thisCenter.x ) , sinAngle * (otherCenter.y - thisCenter.y), 0.0f, 0.0f );
				}
				else
					hyp = Vector4( sinAngle * (otherCenter.x - thisCenter.x), cosAngle * (otherCenter.y - thisCenter.y), 0.0f, 0.0f );
			}



			
			// Get the normal vector to the colliding object
			Vector4 normal(hyp.normalize(hyp));
			// Calculate a new velocity
			*velocity = normal * (velocity->dot(normal) * -2.0f) + *velocity;
			// Separate collided objects (upon collision 2 objects will slightly overlap so this is necessary)
			Matrix4::UpdatePositionMatrix(translationMatrix, velocity->x, velocity->y, 0);

			// NOTE: Corner wonky, need to implement with rotation
		}
	}
}

bool Ball::FlipperCollision(Vector4& otherCenter, Game_Object& other)
{
	Vector4 axis, C, A, B;
	float projC, projA, projB, gap;

	// Calculate the center
	Vector2 thisCenter(this->translationMatrix[0][3], this->translationMatrix[1][3]);

	// Corners of flipper
	Vector4 upperRight(other.sprite->GetRadius().x, other.sprite->GetRadius().y, 0.0f, 0.0f);
	Vector4 upperLeft(-other.sprite->GetRadius().x, other.sprite->GetRadius().y, 0.0f, 0.0f);
	Vector4 bottomRight(other.sprite->GetRadius().x, -other.sprite->GetRadius().y, 0.0f, 0.0f);
	Vector4 bottomLeft(-other.sprite->GetRadius().x, -other.sprite->GetRadius().y, 0.0f, 0.0f);
	// Properly rotate all corners
	upperRight = other.rotationMatrix * upperRight;
	upperLeft = other.rotationMatrix * upperLeft;
	bottomRight = other.rotationMatrix * bottomRight;
	bottomLeft = other.rotationMatrix * bottomLeft;

	// Corners of circle
	Vector4 circleUpperRight( (float)sqrt( pow( this->sprite->GetRadius().x, 2.0f ) / 2.0f ), (float)sqrt( pow( this->sprite->GetRadius().x, 2.0f ) / 2.0f ), 0.0f, 0.0f ); 
	Vector4 circleUpperLeft( (float)-sqrt( pow( this->sprite->GetRadius().x, 2.0f ) / 2.0f ), (float)sqrt( pow( this->sprite->GetRadius().x, 2.0f ) / 2.0f ), 0.0f, 0.0f );
	Vector4 circleBottomRight( (float)sqrt( pow( this->sprite->GetRadius().x, 2.0f ) / 2.0f ), (float)-sqrt( pow( this->sprite->GetRadius().x, 2.0f ) / 2.0f ), 0.0f, 0.0f );
	Vector4 circleBottomLeft( (float)-sqrt( pow( this->sprite->GetRadius().x, 2.0f ) / 2.0f ), (float)-sqrt( pow( this->sprite->GetRadius().x, 2.0f ) / 2.0f ), 0.0f, 0.0f );
	// Properly rotate all corners
	circleUpperRight = other.rotationMatrix * circleUpperRight;
	circleUpperLeft = other.rotationMatrix * circleUpperLeft;
	circleBottomRight = other.rotationMatrix * circleBottomRight;
	circleBottomLeft = other.rotationMatrix * circleBottomLeft;

	// Axis 1
	// Calculate axis, 3 vectors, the dot, and then the gap
	axis = Vector4( (upperRight - upperLeft).normalize(upperRight - upperLeft) );
	C = Vector4(otherCenter.x - thisCenter.x, otherCenter.y - thisCenter.y, 0.0f, 0.0f);
	A = Vector4(circleUpperRight);
	B = Vector4(upperRight);

	projC = C.dot(axis);
	projA = A.dot(axis);
	projB = B.dot(axis);
	gap = abs(projC) - abs(projA) - abs(projB);	

	// Check value of gap
	if(gap > 0)
		return false;

	// Axis 2
	// Calculate axis, 3 vectors, the dot, and then the gap
	axis = Vector4( (bottomRight - bottomLeft).normalize(bottomRight - bottomLeft) );
	C = Vector4(otherCenter.x - thisCenter.x, otherCenter.y - thisCenter.y, 0.0f, 0.0f);
	A = Vector4(circleBottomRight);
	B = Vector4(bottomRight);

	projC = C.dot(axis);
	projA = A.dot(axis);
	projB = B.dot(axis);
	gap = abs(projC) - abs(projA) - abs(projB);	

	// Check value of gap
	if(gap > 0)
		return false;

	// Axis 3
	// Calculate axis, 3 vectors, the dot, and then the gap
	axis = Vector4( (upperRight - bottomRight).normalize(upperRight - bottomRight) );
	C = Vector4(otherCenter.x - thisCenter.x, otherCenter.y - thisCenter.y, 0.0f, 0.0f);
	A = Vector4(circleBottomRight);
	B = Vector4(bottomRight);

	projC = C.dot(axis);
	projA = A.dot(axis);
	projB = B.dot(axis);
	gap = abs(projC) - abs(projA) - abs(projB);	

	// Check value of gap
	if(gap > 0)
		return false;

	// Axis 4
	// Calculate axis, 3 vectors, the dot, and then the gap
	axis = Vector4( (upperLeft - upperLeft).normalize(upperLeft - upperLeft) );
	C = Vector4(otherCenter.x - thisCenter.x, otherCenter.y - thisCenter.y, 0.0f, 0.0f);
	A = Vector4(circleBottomLeft);
	B = Vector4(bottomLeft);

	projC = C.dot(axis);
	projA = A.dot(axis);
	projB = B.dot(axis);
	gap = abs(projC) - abs(projA) - abs(projB);	

	// Check value of gap
	if(gap > 0)
		return false;

	return true;
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
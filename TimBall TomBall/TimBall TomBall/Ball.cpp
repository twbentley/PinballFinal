#include "Ball.h"

// Default constructor
Ball::Ball() { }

// Parameterized constructor : base()
Ball::Ball(Polygon* sprite_name, Vector4 color, float positionX, float positionY, float velX, float velY, float scaleX, float scaleY) : Game_Object( sprite_name, color, positionX, positionY, scaleX, scaleY )
{
	// Initialize fields
	velocity = Vector4(velX, velY, 0.0f, 0.0f);
	accel = Vector4(0.0f, -0.1f, 0.0f, 0.0f);

	launched = false;
}

// Destructor
Ball::~Ball(void) { }

// Update the ball. Move it and return the state of its collision
int Ball::Update(unordered_map<string, Game_Object*> objects, int& ballCount)
{
	// If the ball is in play, move it based on velocity, acceleration/gravity
	if(launched)
	{
		Matrix4::UpdatePositionMatrix(translationMatrix, velocity.x, velocity.y, 0);
		velocity += accel;
	}

	// "Friction"
	//if(accel > 0)
	//	*(accel) += Vector4(-0.01f, 0.0f, 0.0f, 0);
	//else if(accel < 0)
	//	*(accel) += Vector4(0.01f, 0.0f, 0.0f, 0);

	return ProcessCollisions(objects, ballCount);
}

// Check for collision with other objects
int Ball::ProcessCollisions(unordered_map<string, Game_Object*> objects, int& ballCount)
{
	int scoreIncrease = 0;

	// Calculate the center of this ball
	Vector4 thisCenter(this->translationMatrix[0][3], this->translationMatrix[1][3], 0.0f, 0.0f);

	// Check collision with all objects
	for(unordered_map<string, Game_Object*>::iterator itr = objects.begin(); itr != objects.end(); itr++)
	{
		// If not launched yet
		if(!launched)
		{
			// If it collided with a spring
			if(itr->first == "Spring")
			{
				// Move the ball to the top of the spring
				translationMatrix = Matrix4::CreatePositionMatrix(itr->second->translationMatrix[0][3], itr->second->translationMatrix[1][3] + itr->second->radius.y + radius.y, 0);
				
				// Launch the ball
				if(static_cast<Spring*>(itr->second)->finished == true)
				{
					launched = true;
					velocity = Vector4(0.0f, 12.0f, 0.0f, 0.0f);
				}
			}
		}
		// If the ball has been launched
		else
		{
			// Calculate the center of the object to check and the combined radius of the ball's and the object's
			Vector4 otherCenter(itr->second->translationMatrix[0][3], itr->second->translationMatrix[1][3], 0.0f, 0.0f);
			Vector4 combinedRadius = this->GetRadius() + itr->second->GetRadius();

			// Check for collision with outside walls, and bounce the ball off of them
			if(itr->first == "WallLeft" && thisCenter.x - GetRadius().x < otherCenter.x + itr->second->GetRadius().x)
			{
				velocity.x += this->velocity.x * -2.0f;
				Matrix4::UpdatePositionMatrix(translationMatrix, velocity.x, velocity.y, 0);

			}
			if(itr->first == "WallRight" && thisCenter.x + GetRadius().x > otherCenter.x - itr->second->GetRadius().x)
			{
				velocity.x += this->velocity.x * -2.0f;
				Matrix4::UpdatePositionMatrix(translationMatrix, velocity.x, velocity.y, 0);
			}
			if(itr->first == "WallTop" && thisCenter.y + GetRadius().x > otherCenter.y - itr->second->GetRadius().y)
			{
				velocity.y += this->velocity.y * -2.0f;
				Matrix4::UpdatePositionMatrix(translationMatrix, velocity.x, velocity.y, 0);
			}
			if(itr->first == "WallBottom" && thisCenter.y - GetRadius().x < otherCenter.y + itr->second->GetRadius().y)
			{
				// If the bottom of the world was hit, lose a ball
				velocity.y += this->velocity.y * -2.0f;
				launched = false;
				ballCount -= 1;
			}


			// Detect spherical collision
			if( ( itr->first.find("Ball") != string::npos || itr->first.find("Bumper") != string::npos /*|| itr->first == "Flipper1"*/) && 
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
				velocity = normal * (velocity.dot(normal) * -2.0f) + velocity;
				// Separate collided objects (upon collision 2 objects will slightly overlap so this is necessary)
				Matrix4::UpdatePositionMatrix(translationMatrix, velocity.x, velocity.y, 0);

				// NOTE: Ball-Ball collision sometimes only changes the velocity of one of the balls

				// If the ball collided with a spherical bumper, squish the bumper
				if(static_cast<Bumper*>(itr->second)->complete)
				{
					static_cast<Bumper*>(itr->second)->complete = false;
					static_cast<Bumper*>(itr->second)->growing = true;
					static_cast<Bumper*>(itr->second)->moveTimes = 5;
				}

				// Increase score for hitting another ball or bumper
				scoreIncrease += 5;
			}

			// Angle of reflection (angle of flipper)
			float bounceAngle = 0.0f;
			bool hitCorner = false;
			if((itr->first.find("Flipper") != string::npos || itr->first.find("InnerWall") != string::npos || itr->first.find("Spinner") != string::npos) && FlipperCollision(otherCenter, *(itr->second), bounceAngle, hitCorner))
			{
				// Calculate the sine/cos of the angle of the flipper, inner wall, spinner, and get that object's radius
				Vector4 flipperRadius(itr->second->GetRadius().x, itr->second->GetRadius().y, 0.0f, 0.0f);
				GLfloat cosAngle(itr->second->rotationMatrix[0][0]);
				GLfloat sinAngle(-itr->second->rotationMatrix[0][1]);

				// Calculate angle of impact
				GLfloat hitAngle = atan(velocity.y/velocity.x) + PI;

				// If the object was a spinner, start spinning it
				if(itr->first.find("Spinner") != string::npos)
					static_cast<Spinner*>(itr->second)->Spin(hitAngle, velocity, this);

				// If you didn't hit the corner of the object
				if(!hitCorner)
				{			
					// Calculate the angle of impact
					if(velocity.x < 0)
						hitAngle += 180 * PI / 180;
					else if(velocity.x >= 0 && velocity.y < 0)
						hitAngle += 360 * PI / 180;
					
					// 360 degrees should be treated as 0 degrees
					if(hitAngle >= 2*PI - .0000002 && hitAngle <= 2*PI + .0000002)
						hitAngle = 0.0f;

					bounceAngle = PI - hitAngle - 2 * bounceAngle;
						if(bounceAngle < 0)
							bounceAngle += 2 * PI;
				}

				// Get the length of the velocity vector
				float length = velocity.length();
			
				// Get a vector based on the magnitude of the velocity and the angle of the collided object
				Vector4 normal(length * cos(bounceAngle), length * sin(bounceAngle), 0.0f, 0.0f);

				// Set the new velocity of the ball to the calculated value
				velocity = normal;

				// Separate collided objects (upon collision 2 objects will slightly overlap so this is necessary)
				Matrix4::UpdatePositionMatrix(translationMatrix, velocity.x, velocity.y, 0);
				
				// Increase score if hit spinner
				if(itr->first.find("Spinner") != string::npos)
				{
					scoreIncrease += 5;
				}
			}
		}
	}

	return scoreIncrease;
}

// Separating Axis Theorem collision with rectangle objects
bool Ball::FlipperCollision(Vector4& otherCenter, Game_Object& other, float& angle, bool& hitCorner)
{
	// Declare helpful locals
	Vector4 axis, C, A, B;
	float projC, projA, projB, gap;

	// Calculate the center
	Vector2 thisCenter(this->translationMatrix[0][3], this->translationMatrix[1][3]);

	// Corners of flipper
	Vector4 upperRight(other.GetRadius().x, other.GetRadius().y, 0.0f, 0.0f);
	Vector4 upperLeft(-other.GetRadius().x, other.GetRadius().y, 0.0f, 0.0f);
	Vector4 bottomRight(other.GetRadius().x, -other.GetRadius().y, 0.0f, 0.0f);
	Vector4 bottomLeft(-other.GetRadius().x, -other.GetRadius().y, 0.0f, 0.0f);
	// Properly rotate all corners
	upperRight = other.rotationMatrix * upperRight;
	upperLeft = other.rotationMatrix * upperLeft;
	bottomRight = other.rotationMatrix * bottomRight;
	bottomLeft = other.rotationMatrix * bottomLeft;

	// Corners of circle
	Vector4 circleUpperRight( (float)sqrt( pow( this->GetRadius().x, 2.0f ) / 2.0f ), (float)sqrt( pow( this->GetRadius().x, 2.0f ) / 2.0f ), 0.0f, 0.0f ); 
	Vector4 circleUpperLeft( (float)-sqrt( pow( this->GetRadius().x, 2.0f ) / 2.0f ), (float)sqrt( pow( this->GetRadius().x, 2.0f ) / 2.0f ), 0.0f, 0.0f );
	Vector4 circleBottomRight( (float)sqrt( pow( this->GetRadius().x, 2.0f ) / 2.0f ), (float)-sqrt( pow( this->GetRadius().x, 2.0f ) / 2.0f ), 0.0f, 0.0f );
	Vector4 circleBottomLeft( (float)-sqrt( pow( this->GetRadius().x, 2.0f ) / 2.0f ), (float)-sqrt( pow( this->GetRadius().x, 2.0f ) / 2.0f ), 0.0f, 0.0f );
	// Properly rotate all corners
	circleUpperRight = other.rotationMatrix * circleUpperRight;
	circleUpperLeft = other.rotationMatrix * circleUpperLeft;
	circleBottomRight = other.rotationMatrix * circleBottomRight;
	circleBottomLeft = other.rotationMatrix * circleBottomLeft;

	// Axis 1 (top)
	// Calculate axis of projection, 3 vectors(ball,object,distance between them, the projection of all those vectors, and then the gap between the objects
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

	// Axis 2 (bottom)
	// Calculate axis of projection, 3 vectors(ball,object,distance between them, the projection of all those vectors, and then the gap between the objects
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

	// Axis 3 (right)
	// Calculate axis of projection, 3 vectors(ball,object,distance between them, the projection of all those vectors, and then the gap between the objects
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

	// Axis 4 (left)
	// Calculate axis of projection, 3 vectors(ball,object,distance between them, the projection of all those vectors, and then the gap between the objects
	axis = Vector4( (upperLeft - bottomLeft).normalize(upperLeft - bottomLeft) );
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

	// Get the current angle of the collided object
	float currentAngle = acos(other.rotationMatrix[0][0]);
	// Calculate the distance from the corners of the object to the circle (magnitude)
	float distanceUpperLeft = ( (upperLeft + otherCenter) - Vector4(thisCenter.x, thisCenter.y, 0.0f, 0.0f )).length();
	float distanceLowerLeft = ( (bottomLeft + otherCenter) - Vector4(thisCenter.x, thisCenter.y, 0.0f, 0.0f )).length();
	float distanceUpperRight = ( (upperRight + otherCenter) - Vector4(thisCenter.x, thisCenter.y, 0.0f, 0.0f )).length();
	float distanceLowerRight = ( (bottomRight + otherCenter) - Vector4(thisCenter.x, thisCenter.y, 0.0f, 0.0f )).length();

	// Instantiate voronoi vectors (one for each cardinal direction)
	Vector4 top(0.0f, 10.0f, 0.0f, 0.0f);
	Vector4 bot(0.0f, -10.0f, 0.0f, 0.0f);
	Vector4 left(-10.0f, 0.0f, 0.0f, 0.0f);
	Vector4 right(10.0f, 0.0f, 0.0f, 0.0f);
	// Rotation voronoi vectors to match flipper rotation
	top = other.rotationMatrix * top;
	bot = other.rotationMatrix * bot;
	left = other.rotationMatrix * left;
	right = other.rotationMatrix * right;
	
	// Calculate vectors between the center of the ball and the corners of the object
	Vector4 testUpperLeft( Vector4(thisCenter.x, thisCenter.y, 0.0f, 0.0f) - otherCenter - upperLeft);;
	Vector4 testUpperRight( Vector4(thisCenter.x, thisCenter.y, 0.0f, 0.0f) - otherCenter - upperRight);
	Vector4 testBottomLeft( Vector4(thisCenter.x, thisCenter.y, 0.0f, 0.0f) - otherCenter - bottomLeft);
	Vector4 testBottomRight( Vector4(thisCenter.x, thisCenter.y, 0.0f, 0.0f) - otherCenter - bottomRight);

	// Check for the quadrant in which the ball collided with the object.
	// Once quadrant has been determined, set angle for ball's new velocity
	//upper-left|   upper  | upper-right
	//       ___|__________|____
	//          |          |
	//     left |  object  |right
	//       ___|__________|___
	//     lower|		   | lower
	//	   left |	lower  | right

	// UpperLeft, Upper
	if (testUpperLeft.dot(left) > 0 && testUpperLeft.dot(top) > 0)
	{
		// Upper left quadrant
		hitCorner = true;

		// might have to add this instead of setting
		angle = currentAngle + 3 * PI / 4;
	}
	else if(testUpperLeft.dot(top) > 0 && testUpperLeft.dot(left) < 0 && testUpperLeft.dot(testUpperRight) < 0)
	{
		// Upper quadrant
		angle = currentAngle;

		if(angle <= PI)
			angle = PI - angle;
		else
			angle = 2*PI - angle;
	}

	// BottomRight, Bottom
	else if(testBottomRight.dot(bot) > 0 && testBottomRight.dot(right) > 0)
	{
		// Bottom right quadrant
		hitCorner = true;

		angle = currentAngle + 7 * PI / 4;
	}
	else if(testBottomRight.dot(bot) > 0 && testBottomRight.dot(right) < 0 && testBottomRight.dot(testUpperLeft) < 0)
	{
		// Bottom quadrant
		angle = currentAngle + PI;

		if(angle <= PI)
			angle = PI - angle;
		else
			angle = 2*PI - angle;
	}

	// UpperRight, Right
	else if(testUpperRight.dot(right) > 0 && testUpperRight.dot(top) > 0)
	{
		// Upper right quadrant
		hitCorner = true;

		angle = currentAngle + PI / 4;
	}
	else if(testUpperRight.dot(right) > 0 && testUpperRight.dot(top) < 0 && testUpperRight.dot(testUpperLeft) < 0)
	{
		// Right quadrant
		angle = currentAngle + 3 * PI / 2;

		if(angle <= PI)
			angle = PI - angle;
		else
			angle = 2*PI - angle;
	}

	// BottomLeft, Left
	else if(testBottomLeft.dot(bot) > 0 && testBottomLeft.dot(left) > 0)
	{
		// Bottom left quadrant
		hitCorner = true;

		angle = currentAngle + 5 * PI / 4;
	}
	else if(testBottomLeft.dot(left) > 0 && testBottomLeft.dot(bot) < 0 && testBottomLeft.dot(testBottomRight) < 0)
	{
		// Left quadrant
		angle = currentAngle + PI / 2;

		if(angle <= PI)
			angle = PI - angle;
		else
			angle = 2 * PI - angle;
	}

	return true;
}
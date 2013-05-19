#include "Spinner.h"

// Default constructor
Spinner::Spinner(void) { }

// Parameterized constructor : base()
Spinner::Spinner(Polygon* sprite_name, Vector4 color, float positionX, float positionY, float scaleX, float scaleY) : Game_Object( sprite_name, color, positionX, positionY, scaleX, scaleY )
{
	// Initialize fields to default values
	angularVelocity = 0.0f;
	angle = 0.0f;
}

// Destructor
Spinner::~Spinner(void) { }

// Every update, spin the spinner if it has been hit (with friction)
void Spinner::Update()
{
	// Update elapsed time to keep movement normal no matter the system
	finalTime = (float)glutGet(GLUT_ELAPSED_TIME);
	float dt = (finalTime - initialTime) / 25;

	// If rotating counterclockwise
	if(angle < 0)
	{
		// Rotate spinner by specified amount, and reduce that by the angular velocity each time(aka friction)
		Matrix4::UpdateRotationMatrix(rotationMatrix, 'z', angle * dt);
		angle += angularVelocity* PI / 180;
	}
	// If rotating clockwise
	else if(angle > 0)
	{
		Matrix4::UpdateRotationMatrix(rotationMatrix, 'z', angle * dt);
		angle -= angularVelocity* PI / 180;
	}

	// Set initial time for next calculation
	initialTime = finalTime;
}

// Set the spinner spinning when it has been hit
// Parameters: hitangle - angle of impact, hitvelocity - velocity of impact, ball - ball that hit the spinner
void Spinner::Spin(float hitAngle, Vector4 hitVelocity, Game_Object* ball)
{
	// Check which side of the spinner was hit (4 quadrants)
	CheckSide(ball);
	// Debugging locals
	bool i = isLeft;
	bool j = isTop;

	// If the spinner was hit on the top left or bottom right, set rotation to CCW based on angle of impact
	if( (isLeft && isTop) || (!isLeft && !isTop ) )
		angle = hitAngle;
	// Else if hit bottom left or top right, set rotation to CW
	else if( (!isLeft && isTop) || (isLeft && !isTop) )
		angle = -hitAngle;
	
	// Spin once before update
	if(angle < 0)
	{
		Matrix4::UpdateRotationMatrix(rotationMatrix, 'z', angle);
		angle += angularVelocity* PI / 180;
	}
	else if(angle > 0)
	{
		Matrix4::UpdateRotationMatrix(rotationMatrix, 'z', angle);
		angle -= angularVelocity* PI / 180;
	}

	// Set the angular velocity
	angularVelocity = 1.0f;
}

// Check for the quadrant of impact (upper-left, upper-right, lower-left, lower-right)
void Spinner::CheckSide(Game_Object* ball)
{
	// Get the centers of the objects
	Vector4 ballCenter(ball->translationMatrix[0][3], ball->translationMatrix[1][3], 0.0f, 0.0f);
	Vector4 spinnerCenter(this->translationMatrix[0][3], this->translationMatrix[1][3], 0.0f, 0.0f);

	// Get the points of the corners of the spinners
	Vector4 upperLeft(spinnerCenter.x - this->radius.x, spinnerCenter.y + this->radius.y, 0.0f, 1.0f);
	Vector4 upperRight(spinnerCenter.x + this->radius.x, spinnerCenter.y + this->radius.y, 0.0f, 1.0f);
	Vector4 lowerLeft(spinnerCenter.x - this->radius.x, spinnerCenter.y - this->radius.y, 0.0f, 1.0f);
	Vector4 lowerRight(spinnerCenter.x + this->radius.x, spinnerCenter.y - this->radius.y, 0.0f, 1.0f);

	// Rotate each of the corners to where the spinner corners actually are
	upperLeft = rotationMatrix * upperLeft;
	upperRight = rotationMatrix * upperRight;
	lowerLeft = rotationMatrix * lowerLeft;
	lowerRight = rotationMatrix * lowerRight;

	// Get the distance from the corners to the center of the ball
	float upperLeftDistance = (upperLeft - ballCenter).length();
	float upperRightDistance = (upperRight - ballCenter).length();
	float lowerLeftDistance = (lowerLeft - ballCenter).length();
	float lowerRightDistance = (lowerRight - ballCenter).length();

	// True - closer to left side. False - closer to right side
	isLeft = (upperLeftDistance < upperRightDistance);
	// True - closer to top side. False - closer to bottom side
	isTop = (upperLeftDistance < lowerLeftDistance);

	// Calculate the linear momentum for the spinner
	Vector4 linearMomentum;
	linearMomentum = static_cast<Ball*>(ball)->velocity.cross(ballCenter - upperLeft, static_cast<Ball*>(ball)->velocity);
	float I = ((this->radius.x * 2) * (this->radius.y * this->radius.y * this->radius.y) * 8) / 12;

	// Calculate the angular velocity of the spinner (not used because needed a lot of fiddling)
	angularVelocity = linearMomentum.length() / I;
}
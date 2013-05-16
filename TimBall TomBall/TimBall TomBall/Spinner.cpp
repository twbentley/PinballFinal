#include "Spinner.h"


Spinner::Spinner(void)
{
}

Spinner::Spinner(Polygon* sprite_name, float positionX, float positionY, float scaleX, float scaleY) : Game_Object( sprite_name, positionX, positionY, scaleX, scaleY )
{
	angularVelocity = 0.0f;
	angle = 0.0f;
}

Spinner::~Spinner(void)
{
}

void Spinner::Update()
{
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
}

void Spinner::Spin(float hitAngle, Vector4 hitVelocity, Game_Object* ball)
{
	//angularVelocity = velocity * thisradius
	CheckSide(ball);
	bool i = isLeft;
	bool j = isTop;

	if( (isLeft && isTop) || (!isLeft && !isTop ) )
		angle = hitAngle;
	else if( (!isLeft && isTop) || (isLeft && !isTop) )
		angle = -hitAngle;

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

	angularVelocity = 1.0f;
}

void Spinner::CheckSide(Game_Object* ball)
{
	Vector4 ballCenter(ball->translationMatrix[0][3], ball->translationMatrix[1][3], 0.0f, 0.0f);
	Vector4 spinnerCenter(this->translationMatrix[0][3], this->translationMatrix[1][3], 0.0f, 0.0f);

	Vector4 upperLeft(spinnerCenter.x - this->radius.x, spinnerCenter.y + this->radius.y, 0.0f, 1.0f);
	Vector4 upperRight(spinnerCenter.x + this->radius.x, spinnerCenter.y + this->radius.y, 0.0f, 1.0f);
	Vector4 lowerLeft(spinnerCenter.x - this->radius.x, spinnerCenter.y - this->radius.y, 0.0f, 1.0f);
	Vector4 lowerRight(spinnerCenter.x + this->radius.x, spinnerCenter.y - this->radius.y, 0.0f, 1.0f);

	upperLeft = rotationMatrix * upperLeft;
	upperRight = rotationMatrix * upperRight;
	lowerLeft = rotationMatrix * lowerLeft;
	lowerRight = rotationMatrix * lowerRight;

	float upperLeftDistance = (upperLeft - ballCenter).length();
	float upperRightDistance = (upperRight - ballCenter).length();
	float lowerLeftDistance = (lowerLeft - ballCenter).length();
	float lowerRightDistance = (lowerRight - ballCenter).length();

	isLeft = (upperLeftDistance < upperRightDistance);
	isTop = (upperLeftDistance < lowerLeftDistance);

	Vector4 linearMomentum;
	linearMomentum = static_cast<Ball*>(ball)->velocity->cross(ballCenter - upperLeft, *static_cast<Ball*>(ball)->velocity);
	float I = ((this->radius.x * 2) * (this->radius.y * this->radius.y * this->radius.y) * 8) / 12;

	angularVelocity = linearMomentum.length() / I;
}
#include "Flipper.h"


Flipper::Flipper(void)
{
}

Flipper::Flipper(Polygon* sprite_name, float positionX, float positionY, int angle, float scaleX, float scaleY)
{
	sprite = sprite_name;
	translationMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
	Matrix4::UpdateScaleMatrix(scaleMatrix, scaleX, scaleY, 1.0f);
	Matrix4::UpdateRotationMatrix(rotationMatrix, 'z', angle);

	moving = false;
	flipped = false;

	radius = sprite_name->GetRadius() * Vector4(scaleX, scaleY, 1.0f, 1.0f);
}

Flipper::~Flipper(void)
{
}

void Flipper::Update(string side)
{
	// Horizontal Keyboard-based input
	if(!moving && glfwGetKey(GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		flipped = true;
		moving = true;
		moveTimes = 5;
	}
	else if(!moving && !glfwGetKey(GLFW_KEY_ENTER) == GLFW_PRESS && flipped)
	{
		flipped = false;
		moving = true;
		moveTimes = 5;
	}

	if((flipped && moveTimes > 0 && side == "Left") || (!flipped && moveTimes > 0 && side == "Right"))
	{
		float angletest1 = rotationMatrix.zAngle;

		Matrix4::UpdateRotationMatrix(rotationMatrix, 'z', 15);
		--moveTimes;

		// Bring to 0-180 (180-360 breaks collision and looks same)
		float angle1 = rotationMatrix.zAngle;
		if(angle1 > 180)
		{
			Matrix4::UpdateRotationMatrix(rotationMatrix, 'z', -180);
		}
	}
	else if((flipped && moveTimes > 0 && side == "Right") || (!flipped && moveTimes > 0 && side == "Left"))
	{
		float angletest = rotationMatrix.zAngle;

		Matrix4::UpdateRotationMatrix(rotationMatrix, 'z', -15);
		--moveTimes;

		// Bring to 0-180 (180-360 breaks collision and looks same)
		float angle = rotationMatrix.zAngle;
		if(angle < 0.0f)
		{
			Matrix4::UpdateRotationMatrix(rotationMatrix, 'z', 180);
		}
	}

	if(moving && moveTimes == 0 && !glfwGetKey(GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		moving = false;
	}
}
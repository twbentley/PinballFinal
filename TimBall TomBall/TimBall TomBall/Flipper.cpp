#include "Flipper.h"

// Default constructor
Flipper::Flipper(void) { }

// Parameterized constructor : base()
Flipper::Flipper(Polygon* sprite_name, Vector4 color, float positionX, float positionY, int angle, float scaleX, float scaleY) : Game_Object( sprite_name, color, positionX, positionY, scaleX, scaleY )
{
	// Set the object to the specified rotation about the z axis
	Matrix4::UpdateRotationMatrix(rotationMatrix, 'z', angle);

	// Instantiate boolean flags
	moving = false;
	flipped = false;
}

// Default constructor
Flipper::~Flipper(void) { }

// Update the flipper - user input
void Flipper::Update(string side)
{
	// Horizontal Keyboard-based input
	if((!moving && glfwGetKey(65) == GLFW_PRESS && side == "Left") || (!moving && glfwGetKey(68) == GLFW_PRESS && side == "Right"))
	{
		flipped = true;
		moving = true;
		moveTimes = 5;
	}
	else if((!moving && !glfwGetKey(65) == GLFW_PRESS && flipped && side == "Left") || (!moving && !glfwGetKey(68) == GLFW_PRESS && flipped && side == "Right"))
	{
		flipped = false;
		moving = true;
		moveTimes = 5;
	}

	// Start rotating the specified flipper to max rotation
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

	// The flipper is no longer moving, it will fall back into initial position/rotation
	if((moving && moveTimes == 0 && !glfwGetKey(65) == GLFW_PRESS && side == "Left") || (moving && moveTimes == 0 && !glfwGetKey(68) == GLFW_PRESS && side == "Right"))
	{
		moving = false;
	}
}
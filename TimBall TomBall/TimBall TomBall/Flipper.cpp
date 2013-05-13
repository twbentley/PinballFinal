#include "Flipper.h"


Flipper::Flipper(void)
{
}

Flipper::Flipper(Polygon* sprite_name, float positionX, float positionY)
{
	sprite = sprite_name;
	translationMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
	Matrix4::UpdateRotationMatrix(rotationMatrix, 'z', 0);
}

Flipper::~Flipper(void)
{
}

void Flipper::Update()
{
	//PollUserInput();
}

// Get user input for various purposes
void Flipper::PollUserInput()
{
	// Horizontal Keyboard-based input
	if(glfwGetKey(GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		Matrix4::UpdateRotationMatrix(rotationMatrix, 'z', 1);
	}
}
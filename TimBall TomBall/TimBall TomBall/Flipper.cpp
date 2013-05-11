#include "Flipper.h"


Flipper::Flipper(void)
{
}

Flipper::Flipper(Polygon* sprite_name, float positionX, float positionY)
{
	sprite = sprite_name;
	objectMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
}

Flipper::~Flipper(void)
{
}

void Flipper::Update()
{
	PollUserInput();
}

// Get user input for various purposes
void Flipper::PollUserInput()
{
	// Horizontal Keyboard-based input
	if(glfwGetKey(GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		Matrix4::UpdateRotationMatrix(*objectMatrix, 'z', 1);
	}
}
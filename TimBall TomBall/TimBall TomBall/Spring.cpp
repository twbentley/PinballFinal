#include "Spring.h"


Spring::Spring(void)
{
}

Spring::Spring(Polygon* sprite_name, float positionX, float positionY, float scaleX, float scaleY)
{
	sprite = sprite_name;
	translationMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
	objectMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
	
	started = false;
	returning = false;
	finished = false;
	moveTimes = 0;

	radius = sprite_name->GetRadius() * Vector4(scaleX, scaleY, 1.0f, 1.0f);
	startRadius = radius;
}

Spring::~Spring(void)
{
}

void Spring::Update()
{
	finished = false;

	int temp = moveTimes;
	// Horizontal Keyboard-based input
	if(!finished && moveTimes == 0 && glfwGetKey(GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		moveTimes = 20;
		started = true;
	}

	if(started && !returning && moveTimes > 0)
	{
		Matrix4::UpdateScaleMatrix(scaleMatrix, 1.0f, moveTimes * 0.03f + 0.4f, 1.0f);
		radius = Vector4(radius.x, (moveTimes * 0.03f + 0.4f) * startRadius.y, 1.0f, 1.0f);
		--moveTimes;
	}
	else if(returning && moveTimes > 0)
	{
		Matrix4::UpdateScaleMatrix(scaleMatrix, 1.0f, (5 - moveTimes) * 0.12f + 0.4f, 1.0f);
		radius = Vector4(radius.x, ((5 - moveTimes) * 0.12f + 0.4f) * startRadius.y, 1.0f, 1.0f);
		--moveTimes;
	}

	if(started && !returning && moveTimes == 0)
	{
		returning = true;
		moveTimes = 5;
	}

	else if(returning && moveTimes == 0)
	{
		returning = false;
		started = false;
		finished = true;
	}
}
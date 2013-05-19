#include "Spring.h"

// Default constructor
Spring::Spring(void) { }

// Parameterized constructor : base()
Spring::Spring(Polygon* sprite_name, Vector4 color, float positionX, float positionY, float scaleX, float scaleY) : Game_Object( sprite_name, color, positionX, positionY, scaleX, scaleY )
{
	// Initialize fields with default values
	started = false;
	returning = false;
	finished = false;
	moveTimes = 0;

	startRadius = radius;
}

// Destructor
Spring::~Spring(void) { }

// Look for user input to contract and release a spring
void Spring::Update()
{
	finished = false;

	int temp = moveTimes;

	// Horizontal Keyboard-based input
	if(!finished && moveTimes == 0 && glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		moveTimes = 20;
		started = true;
	}

	// Scale the spring towards full contracts
	if(started && !returning && moveTimes > 0)
	{
		Matrix4::UpdateScaleMatrix(scaleMatrix, 1.0f, moveTimes * 0.03f + 0.4f, 1.0f);
		radius = Vector4(radius.x, (moveTimes * 0.03f + 0.4f) * startRadius.y, 1.0f, 1.0f);
		--moveTimes;
	}
	// Scale the spring towards full release
	else if(returning && moveTimes > 0)
	{
		Matrix4::UpdateScaleMatrix(scaleMatrix, 1.0f, (5 - moveTimes) * 0.12f + 0.4f, 1.0f);
		radius = Vector4(radius.x, ((5 - moveTimes) * 0.12f + 0.4f) * startRadius.y, 1.0f, 1.0f);
		--moveTimes;
	}

	// The spring has fully contracted, release it
	if(started && !returning && moveTimes == 0)
	{
		returning = true;
		moveTimes = 5;
	}
	// The spring has finished its movement
	else if(returning && moveTimes == 0)
	{
		returning = false;
		started = false;
		finished = true;
	}
}
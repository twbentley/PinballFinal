#include "Bumper.h"

// Default constructor
Bumper::Bumper(void) { }

// Parameterized constructor : base()
Bumper::Bumper(Polygon* sprite_name, Vector4 color, float positionX, float positionY, float scaleX, float scaleY) : Game_Object( sprite_name, color, positionX, positionY, scaleX, scaleY )
{
	// Initialize fields with default values
	complete = true;
	growing = false;
	shrinking = false;
	moveTimes = 0;
	startRadius = radius;
}

// Destructor
Bumper::~Bumper(void) { }

// Update the bumper to squish if hit
void Bumper::Update(string side)
{
	// Squish bumper based on skew matrix
	if(side == "Left")
	{
		// Skew the ball
		if(growing && moveTimes > 0)
		{
			Matrix4::UpdateSkewMatrix(scaleMatrix, Vector4(((5 - moveTimes) * 0.03f), ((5 - moveTimes) * 0.03f), 0.0f, 0.0f));
			radius = Vector4(((5 - moveTimes) * 0.03f + 1.0f) * startRadius.x, ((5 - moveTimes) * 0.03f + 1.0f) * startRadius.y, 1.0f, 1.0f);
			--moveTimes;
		}
		// Bring the ball back to normal size
		else if(shrinking && moveTimes > 0)
		{
			Matrix4::UpdateSkewMatrix(scaleMatrix, Vector4((moveTimes * 0.03f), (moveTimes * 0.03f), 0.0f, 0.0f));
			radius = Vector4((moveTimes * 0.03f + 1.0f) * startRadius.x, (moveTimes * 0.03f + 1.0f) * startRadius.y, 1.0f, 1.0f);
			--moveTimes;
		}
	}
	// Squish bumper using scale matrix
	else
	{
		// Scale the ball
		if(growing && moveTimes > 0)
		{
			Matrix4::UpdateScaleMatrix(scaleMatrix, (5 - moveTimes) * 0.03f + 1.0f, (5 - moveTimes) * 0.03f + 1.0f, 1.0f);
			radius = Vector4(((5 - moveTimes) * 0.03f + 1.0f) * startRadius.x, ((5 - moveTimes) * 0.03f + 1.0f) * startRadius.y, 1.0f, 1.0f);
			--moveTimes;
		}
		// Bring the ball back to normal size
		else if(shrinking && moveTimes > 0)
		{
			Matrix4::UpdateScaleMatrix(scaleMatrix, moveTimes * 0.03f + 1.0f, moveTimes * 0.03f + 1.0f, 1.0f);
			radius = Vector4((moveTimes * 0.03f + 1.0f) * startRadius.x, (moveTimes * 0.03f + 1.0f) * startRadius.y, 1.0f, 1.0f);
			--moveTimes;
		}
	}

	// Reset fields based on if the bumped is squishing or unsquishing
	if(growing && moveTimes == 0)
	{
		growing = false;
		shrinking = true;
		moveTimes = 5;
	}
	else if(shrinking && moveTimes == 0)
	{
		shrinking = false;
		complete = true;
	}
}

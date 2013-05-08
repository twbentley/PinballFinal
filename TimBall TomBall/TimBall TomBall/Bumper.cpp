#include "Bumper.h"


Bumper::Bumper(void)
{
}

Bumper::Bumper(Polygon* sprite_name, float positionX, float positionY)
{
	sprite = sprite_name;
	objectMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
}

Bumper::~Bumper(void)
{
}

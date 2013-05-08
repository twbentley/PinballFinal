#include "Wall.h"


Wall::Wall(void)
{
}

Wall::Wall(Polygon* sprite_name, float positionX, float positionY)
{
	sprite = sprite_name;
	objectMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
}

Wall::~Wall(void)
{
}

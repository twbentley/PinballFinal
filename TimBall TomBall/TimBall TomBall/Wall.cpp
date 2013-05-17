#include "Wall.h"


Wall::Wall(void)
{
}

Wall::Wall(Polygon* sprite_name, Vector4 color, float positionX, float positionY, float scaleX, float scaleY) : Game_Object( sprite_name, color, positionX, positionY, scaleX, scaleY )
{
}

Wall::~Wall(void)
{
}

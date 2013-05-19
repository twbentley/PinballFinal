#include "Wall.h"

// Default constructor
Wall::Wall(void) { }

// Paramterized constructor : base()
Wall::Wall(Polygon* sprite_name, Vector4 color, float positionX, float positionY, float scaleX, float scaleY) : Game_Object( sprite_name, color, positionX, positionY, scaleX, scaleY )
{
}

// Destructor
Wall::~Wall(void) { }
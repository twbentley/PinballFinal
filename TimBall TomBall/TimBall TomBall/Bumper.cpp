#include "Bumper.h"


Bumper::Bumper(void)
{
}

Bumper::Bumper(Polygon* sprite_name, float positionX, float positionY) : Game_Object( sprite_name, positionX, positionY )
{
	//sprite = sprite_name;
	//translationMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
	//objectMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
}

Bumper::~Bumper(void)
{
}

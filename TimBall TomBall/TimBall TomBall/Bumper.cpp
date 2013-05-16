#include "Bumper.h"


Bumper::Bumper(void)
{
}

Bumper::Bumper(Polygon* sprite_name, float positionX, float positionY, float scaleX, float scaleY)
{
	sprite = sprite_name;
	translationMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);
	objectMatrix = Matrix4::CreatePositionMatrix(positionX, positionY, 0.0f);

	radius = sprite_name->GetRadius() * Vector4(scaleX, scaleY, 1.0f, 1.0f);
}

Bumper::~Bumper(void)
{
}

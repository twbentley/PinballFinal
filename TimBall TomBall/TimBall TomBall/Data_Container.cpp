#include "Data_Container.h"

Data_Container::Data_Container()
{
	sprites["circle"] = new Polygon("Pinball_Circle");
	sprites["square"] = new Polygon("Pinball_Square");
	sprites["vert_rect"] = new Polygon("Pinball_RectangleVertical");
	sprites["horiz_rect"] = new Polygon("Pinball_RectangleHorizontal");
}
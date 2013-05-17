#include "Data_Container.h"

Data_Container::Data_Container()
{
	sprites["circle"] = new Polygon("Pinball_Circle");
	sprites["square"] = new Polygon("Pinball_Square");
	sprites["horiz_rect"] = new Polygon("Pinball_RectangleHorizontal");
	sprites["vert_rect"] = new Polygon("Pinball_RectangleVertical");
	sprites["flipper"] = new Polygon("Pinball_RectangleHorizontal");
	sprites["spring"] = new Polygon("Pinball_Spring");
}

Data_Container::~Data_Container()
{
	//sprites.clear();
	for(unordered_map<string, Polygon*>::iterator itr = sprites.begin(); itr != sprites.end(); itr++)
		delete itr->second;
}
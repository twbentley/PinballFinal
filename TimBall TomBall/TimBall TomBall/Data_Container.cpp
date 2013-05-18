#include "Data_Container.h"

// Constructor
Data_Container::Data_Container()
{
	// Instantiate each type of sprite
	sprites["circle"] = new Polygon("Pinball_Circle");
	sprites["square"] = new Polygon("Pinball_Square");
	sprites["horiz_rect"] = new Polygon("Pinball_RectangleHorizontal");
	sprites["vert_rect"] = new Polygon("Pinball_RectangleVertical");
	sprites["flipper"] = new Polygon("Pinball_RectangleHorizontal");
	sprites["spring"] = new Polygon("Pinball_Spring");
}

// Destructor
Data_Container::~Data_Container()
{
	// Clean up memory
	for(unordered_map<string, Polygon*>::iterator itr = sprites.begin(); itr != sprites.end(); itr++)
		delete itr->second;
}
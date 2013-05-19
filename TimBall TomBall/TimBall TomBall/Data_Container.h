// Author: Timothy Reynolds
// Contributor: Thomas Bentley

#ifndef DATA_CONTAINER_H
#define DATA_CONTAINER_H

#include "Polygon.h"
#include "ColorShader.h"
#include <string>
#include <unordered_map>

// This class holds model data/sprites for objects
class Data_Container
{
private:
	
public:
	Data_Container();
	~Data_Container();

	unordered_map<string, Polygon*> sprites;
};

#endif
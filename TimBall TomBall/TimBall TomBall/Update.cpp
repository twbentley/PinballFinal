#include "Update.h"

Update::Update(void)
{
}

Update::~Update(void)
{
}

// Update position, velocity, etc of game objects
void Update::Update_Game(unordered_map<char*, Game_Object*> objects)
{
	static_cast<Ball*>(objects["Ball"])->Update(objects);

	/*for(unordered_map<char*, Game_Object*>::iterator itr = objects.begin(); itr != objects.end(); itr++)
	{
		// TODO::If check for appropriate type of object, Check based on dictionary name
		if(itr->first == "Ball")
		{
			static_cast<Ball*>(itr->second)->Update();
		}
	}*/
}
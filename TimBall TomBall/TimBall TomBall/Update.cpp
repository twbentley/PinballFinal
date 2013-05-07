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
	for(unordered_map<char*, Game_Object*>::iterator itr = objects.begin(); itr != objects.end(); itr++)
	{
		(*itr).second->Update();
	}
}
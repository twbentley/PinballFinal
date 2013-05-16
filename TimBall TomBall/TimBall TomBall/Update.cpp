#include "Update.h"

Update::Update(void)
{
}

Update::~Update(void)
{
}

// Update position, velocity, etc of game objects
void Update::Update_Game(unordered_map<string, Game_Object*> objects)
{
	static_cast<Ball*>(objects["Ball1"])->Update(objects);
	//static_cast<Ball*>(objects["Ball2"])->Update(objects);
	static_cast<Flipper*>(objects["Flipper1"])->Update("Left");
	static_cast<Flipper*>(objects["Flipper2"])->Update("Right");
	static_cast<Spring*>(objects["Spring"])->Update();
	static_cast<Spinner*>(objects["Spinner"])->Update();
}
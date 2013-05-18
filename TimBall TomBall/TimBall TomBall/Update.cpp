#include "Update.h"

Update::Update(void)
{
}

Update::~Update(void)
{
}

// Update game objects and switch between menu and game states
// If you remove any objects from the game world, remove their update here or the game will error
void Update::Update_Game(string& gameState, unordered_map<string, Game_Object*> objects)
{
	// If in the menu, ENTER will bring you to the game
	if(gameState == "Menu")
	{
		if(glfwGetKey(GLFW_KEY_ENTER) == GLFW_PRESS)
		{
			gameState = "Game";
		}
	}
	else if(gameState == "Game")
	{
		static_cast<Ball*>(objects["Ball1"])->Update(objects);
	
		static_cast<Flipper*>(objects["Flipper1"])->Update("Left");
		static_cast<Flipper*>(objects["Flipper2"])->Update("Right");
	
		static_cast<Spring*>(objects["Spring"])->Update();
		static_cast<Spinner*>(objects["Spinner"])->Update();

		static_cast<Bumper*>(objects["Bumper1"])->Update("Left");
		static_cast<Bumper*>(objects["Bumper2"])->Update("Right");
	}
}
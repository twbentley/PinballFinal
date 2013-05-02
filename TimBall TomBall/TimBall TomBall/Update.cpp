#include "Update.h"

Update::Update(void)
{
}

Update::~Update(void)
{
}

// Update position, velocity, etc of game objects
void Update::Update_Game(Game_Object* testObject)
{
	testObject->Update();
	// Increase or decrease radius and number of sides of polygon based on ARROW KEYS
	//if(glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS)
	//	Setup_Polygon(++num_sides, poly_radius);
	//else if(glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS && num_sides > 3)		// Don't allow polygons under 2 sides
	//	Setup_Polygon(--num_sides, poly_radius);
	//else if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
	//	Setup_Polygon(num_sides, poly_radius + .01f);
	//else if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS && poly_radius > 0.02)	// Don't allow radii under .02
	//	Setup_Polygon(num_sides, poly_radius - .01f);

	//// Move polygon based on num_pad arrow keys
	//if(glfwGetKey(GLFW_KEY_KP_8))		// Move up
	//	for(int i = 0; i < num_sides; i++)
	//		points[i].y += 0.01f;
	//else if(glfwGetKey(GLFW_KEY_KP_2))	// Move down
	//	for(int i = 0; i < num_sides; i++)
	//		points[i].y -= 0.01f;
	//else if(glfwGetKey(GLFW_KEY_KP_4))	// Move left
	//	for(int i = 0; i < num_sides; i++)
	//		points[i].x -= 0.01f;
	//else if(glfwGetKey(GLFW_KEY_KP_6))	// Move right
	//	for(int i = 0; i < num_sides; i++)
	//		points[i].x += 0.01f;
	// THE ABOVE CODE IS SHORTER WITHOUT PARENS, BUT LOOKS HORRIBLE WITHOUT THEM
}
#include "Game.h"

// Polygon Fields:
// Points for the polygon
Vector2* points;
// Number of sides of the polygon
int num_sides;
// Radius of the polygon
GLfloat poly_radius;
// Array of color for the polygon
GLfloat Poly_Color[3] = { 1.0, 0.0, 0.0 };

// Define for leak detection
#define _CRTDBG_MAP_ALLOC

// Prevent console window from opening
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

// Forward declarations
void Main_Loop();
void Setup_Polygon(int num_sides, GLfloat radius);
void Update();

int main()
{
	Game* game = new Game();

	while( (*game).Game_Loop() );
}
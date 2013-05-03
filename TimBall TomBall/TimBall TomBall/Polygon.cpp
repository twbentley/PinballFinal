#include "Polygon.h"

Polygon::Polygon()
{
	num_sides = 3;
	radius = 0.5f;
	points = new Vector2[num_sides];
	points2 = new Vector4[num_sides];

	GLfloat x, y, theta = 0;
    for (int i=0; i < 3 ; i++) 
	{
        // Set the angle and use that to get x and y points (first point will fall on 2PI/(0,1))
        theta += static_cast<GLfloat>( (2 * PI / 1) / 3);
        x = static_cast<GLfloat>( radius * cos(theta + PI / 2) );
        y = static_cast<GLfloat>( radius * sin(theta + PI / 2) );
        points[i] = Vector2(x,y);
		points2[i] = Vector4(x,y,0,0);
    }

	// Create a vertex array object
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

	glGenBuffers( 1, &buffer );
	glBindBuffer( GL_ARRAY_BUFFER, buffer);
	glBufferData( GL_ARRAY_BUFFER, sizeof(Vector2) * num_sides, points2, GL_STATIC_DRAW );
}

Polygon::~Polygon(void)
{
}

// Draw a polygon using an array of points
void Polygon::Draw(ColorShader* shader, Matrix4* worldMatrix, Matrix4* viewMatrix, Matrix4* projectionMatrix)
{
	glBindVertexArray( vao );
	glBindBuffer( GL_ARRAY_BUFFER, buffer);
	shader->Render(worldMatrix, viewMatrix, projectionMatrix, num_sides);

	// OLD
	//// Draw polygon
	//for(int j = 0; j < num_sides; j++)
	//{
	//	// Set the draw color
	//	glColor3f(0.0, 1.0, 0.0);

	//	// Draw triangle using using desired vertex
	//	glVertex2f(points[j].x + position->x, points[j].y + position->y);

	//	// If we +finish drawing the vertices, connect the first and last vertices
	//	j != (num_sides - 1) ? glVertex2f(points[0].x + position->x, points[0].y + position->y) : NULL;
	//}
}
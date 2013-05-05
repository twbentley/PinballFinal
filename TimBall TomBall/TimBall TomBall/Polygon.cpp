#include "Polygon.h"

Polygon::Polygon()
{
	num_sides = 3;
	radius = 0.5f;
	//points = new Vector2[num_sides];
	points = new Vector4[num_sides];

	//GLfloat x, y, theta = 0;
 //   for (int i=0; i < num_sides ; i++) 
	//{
 //       // Set the angle and use that to get x and y points (first point will fall on 2PI/(0,1))
 //       theta += static_cast<GLfloat>( (2 * PI / 1) / num_sides);
 //       x = static_cast<GLfloat>( radius * cos(theta + PI / 2));
 //       y = static_cast<GLfloat>( radius * sin(theta + PI / 2));
 //       
	//	points[i] = Vector4(x, y, 0, 0);
 //   }

	points[0] = Vector4(-200.0f, -200.0f, 0, 1);
	points[1] = Vector4(-200.0f, 200.0f, 0, 1);
	points[2] = Vector4(200.0f, 200.0f, 0, 1);

	glGenBuffers( 1, &buffer );
	glBindBuffer( GL_ARRAY_BUFFER, buffer);
	glBufferData( GL_ARRAY_BUFFER, sizeof(Vector4) * num_sides, points, GL_STATIC_DRAW );
}

Polygon::~Polygon(void)
{
}

// Draw a polygon using an array of points
void Polygon::Draw(ColorShader* shader, Matrix4* worldMatrix, Matrix4* viewMatrix, Matrix4* projectionMatrix)
{
	Vector4 temp[3];
	temp[0] = Vector4( *worldMatrix * points[0] );
	temp[0] = Vector4(*viewMatrix * temp[0] );
	temp[0] = Vector4(*projectionMatrix * temp[0] );
	temp[1] = Vector4( *worldMatrix * points[1] );
	temp[1] = Vector4(*viewMatrix * temp[1] );
	temp[1] = Vector4(*projectionMatrix * temp[1] );
	temp[2] = Vector4( *worldMatrix * points[2] );
	temp[2] = Vector4(*viewMatrix * temp[2] );
	temp[2] = Vector4(*projectionMatrix * temp[2] );

	glBindBuffer( GL_ARRAY_BUFFER, buffer);
	shader->Render(worldMatrix, viewMatrix, projectionMatrix, num_sides);
}
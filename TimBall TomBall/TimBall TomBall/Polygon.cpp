#include "Polygon.h"

Polygon::Polygon()
{
	numIndices = 6;
	radius = 0.5f;
	//points = new Vector2[num_sides];
	vertices = new Vector4[numIndices - 2];
	indices = new unsigned int[numIndices];

	vertices[0] = Vector4(-100.0f, -100.0f, 0, 1);
	vertices[1] = Vector4(-100.0f, 100.0f, 0, 1);
	vertices[2] = Vector4(100.0f, 100.0f, 0, 1);
	vertices[3] = Vector4(100.0f, -100.0f, 0, 1);
	//points[4] = Vector4(125.0f, 200.0f, 0, 1);
	//points[5] = Vector4(0.0f, 100.0f, 0, 1);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;
	indices[4] = 2;
	indices[5] = 0;

	glGenBuffers( 1, &vertexBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData( GL_ARRAY_BUFFER, sizeof(Vector4) * (numIndices - 2), vertices, GL_STATIC_DRAW );

	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW);

}

Polygon::~Polygon(void)
{
}

// Draw a polygon using an array of points
void Polygon::Draw(ColorShader* shader, Matrix4* worldMatrix, Matrix4* viewMatrix, Matrix4* projectionMatrix)
{
	Vector4 temp[4];
	temp[0] = Vector4( *worldMatrix * vertices[0] );
	temp[0] = Vector4(*viewMatrix * temp[0] );
	temp[0] = Vector4(*projectionMatrix * temp[0] );
	temp[1] = Vector4( *worldMatrix * vertices[1] );
	temp[1] = Vector4(*viewMatrix * temp[1] );
	temp[1] = Vector4(*projectionMatrix * temp[1] );
	temp[2] = Vector4( *worldMatrix * vertices[2] );
	temp[2] = Vector4(*viewMatrix * temp[2] );
	temp[2] = Vector4(*projectionMatrix * temp[2] );
	temp[3] = Vector4( *worldMatrix * vertices[3] );
	temp[3] = Vector4(*viewMatrix * temp[3] );
	temp[3] = Vector4(*projectionMatrix * temp[3] );

	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	shader->Render(worldMatrix, viewMatrix, projectionMatrix, numIndices);
}
#include "Polygon.h"

Polygon::Polygon()
{}

Polygon::Polygon(string modelToLoad)
{
	vector<float> modelData[11];
	FileIO::LoadObject("Assets/" + modelToLoad + ".obj", &(modelData[0]));

	numIndices = modelData[8].size();

	radius = 0.5f;
	//points = new Vector2[num_sides];
	vertices = new Vector4[numIndices];
	indices = new unsigned int[numIndices];

	// Load in vertices based on obj indices setup
	// COMMENTS FOR TEXTURING/LIGHTING IF WE DECIDE TO IMPLEMENT
	int currentPositionIndex;
	//int currentTextureIndex;
	//int currentNormalIndex;
	for(int i = 0; i < modelData[8].size(); i++)
	{
		currentPositionIndex = modelData[8][i];
		//currentTextureIndex = modelData[9][i];
		//currentNormalIndex = modelData[10][i];

		vertices[i] = Vector4(modelData[0][currentPositionIndex] * 200, modelData[1][currentPositionIndex] * 200, modelData[2][currentPositionIndex] * 200, 1.0f);
		//vertices[i].position = D3DXVECTOR3(modelData[0][currentPositionIndex], modelData[1][currentPositionIndex], modelData[2][currentPositionIndex]);
		//vertices[i].texture = D3DXVECTOR2(modelData[3][currentTextureIndex], modelData[4][currentTextureIndex]);
		//vertices[i].normal = D3DXVECTOR3(modelData[5][currentNormalIndex], modelData[6][currentNormalIndex], modelData[7][currentNormalIndex]);
	}
	// Load in indices, swapping direction the triangles are drawn (for converting from right hand to left hand system)
	for(int i = 0; i < modelData[8].size(); i++)
	{
		indices[i] = i;
	}

	Vector4 i = vertices[indices[0]];
	Vector4 ii = vertices[indices[1]];
	Vector4 iii = vertices[indices[2]];

	//vertices[0] = Vector4(-100.0f, -100.0f, 0, 1);
	//vertices[1] = Vector4(-100.0f, 100.0f, 0, 1);
	//vertices[2] = Vector4(100.0f, 100.0f, 0, 1);
	//vertices[3] = Vector4(100.0f, -100.0f, 0, 1);

	//indices[0] = 0;
	//indices[1] = 1;
	//indices[2] = 2;
	//indices[3] = 3;
	//indices[4] = 2;
	//indices[5] = 0;

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
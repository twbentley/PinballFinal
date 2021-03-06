#include "Polygon.h"

// Scaling factor for objects
const int OBJ_CONST = 12;

// Default constructor
Polygon::Polygon() { }

// Parameterized constructor
// modelToload - file name for the current model
Polygon::Polygon(string modelToLoad)
{
	// Load the model file
	vector<float> modelData[11];
	FileIO::LoadObject("Assets/" + modelToLoad + ".obj", &(modelData[0]));

	// Instantiate arrays
	numIndices = modelData[8].size();
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

		vertices[i] = Vector4(modelData[0][currentPositionIndex] * OBJ_CONST, modelData[1][currentPositionIndex] * OBJ_CONST, modelData[2][currentPositionIndex] * OBJ_CONST, 1.0f);
		//vertices[i].position = D3DXVECTOR3(modelData[0][currentPositionIndex], modelData[1][currentPositionIndex], modelData[2][currentPositionIndex]);
		//vertices[i].texture = D3DXVECTOR2(modelData[3][currentTextureIndex], modelData[4][currentTextureIndex]);
		//vertices[i].normal = D3DXVECTOR3(modelData[5][currentNormalIndex], modelData[6][currentNormalIndex], modelData[7][currentNormalIndex]);
	}
	// Load in indices, swapping direction the triangles are drawn (for converting from right hand to left hand system)
	for(int i = 0; i < modelData[8].size(); i++)
	{
		indices[i] = i;
	}

	// Store radius as longest vertex
	for each(float distanceX in modelData[0])
	{
		if(distanceX * OBJ_CONST > radius.x)
		{
			radius.x = distanceX * OBJ_CONST;
		}
	}
	// Store radius as longest vertex
	for each(float distanceY in modelData[1])
	{
		if(distanceY * OBJ_CONST > radius.y)
		{
			radius.y = distanceY * OBJ_CONST;
		}
	}

	// Create a vertex array object
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

	// Create, bind, and populate the vertex buffer
	glGenBuffers( 1, &vertexBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData( GL_ARRAY_BUFFER, sizeof(Vector4) * numIndices, vertices, GL_STATIC_DRAW );

	// Create, bind, and populate the index buffer
	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, indices, GL_STATIC_DRAW);

	// Vertices loaded into buffer, don't need data anymore
	delete [] vertices;
}

// Destructor
Polygon::~Polygon(void)
{
	// Release buffers
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexbuffer);
		
	delete indices;
}

// Draw a polygon using an array of points
void Polygon::Draw(ColorShader* shader, Matrix4 worldMatrix, Matrix4 viewMatrix, Matrix4 projectionMatrix, Vector4 color)
{
	//glEnableVertexAttribArray(vao);

	// Swap the to the correct buffer for the object (vertices and indices)
	glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);

	// Render object using the shader
	shader->Render(&worldMatrix, &viewMatrix, &projectionMatrix, numIndices, color);

	//glDisableVertexAttribArray(vao);
}

// Getter for the radius of a polygon
Vector4 Polygon::GetRadius()
{ 
	return radius; 
}

////////////////////////////////////////////////////////////////////////////////
// Filename: FileIO.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FileIO.h"

ifstream FileIO::loader;

// Default constructor
FileIO::FileIO() { }

// Parameterized Constructor
FileIO::FileIO(const FileIO& other) { }

// Destructor
FileIO::~FileIO() { }

// 3D model standard .obj file importer
void FileIO::LoadObject(string objFile, vector<float>* const& model)
{
	// File setup, a face is a triangle or square
	// 1/1/1 face means use position 1, texture 1, normal 1
	char input;
	float data;

	loader.open(objFile);

	// Pass by unecessary text and get to the positions
	input = loader.get();
	while(input != 'v')
	{
		// stuck in this loop
		input = loader.get();
	}

	// Go through all positions and assign
	while(input != 't')
	{
		loader >> data;
		model[0].push_back(data);
		loader >> data;
		model[1].push_back(data);
		
		loader >> data;
		// Negate the z (converting from right hand to left hand)
		data *= -1;
		model[2].push_back(data);

		// Continue and also check to confirm still reading in the same data
		input = loader.get();
		input = loader.get();
		input = loader.peek();
	}
	
	// Go through all textures and assign
	input = loader.get();
	while(input != 'n')
	{
		// Get the three values
		loader >> data;
		model[3].push_back(data);

		loader >> data;
		// Y is 1 - data (converting from left hand to right hand system)
		data = 1.0f - data;
		model[4].push_back(data);

		// Continue and also check to confirm still reading in the same data
		input = loader.get();
		input = loader.get();
		input = loader.get();
	}

	// Go through all normals and assign
	while(input != ' ')
	{
		loader >> data;
		model[5].push_back(data);
		loader >> data;
		model[6].push_back(data);

		loader >> data;
		// Negate the z (converting from left hand to right hand system)
		data *= -1.0f;
		model[7].push_back(data);

		// Continue and also check to confirm still reading in the same data
		input = loader.get();
		input = loader.get();
		input = loader.get();
	}

	// Get the faces/sides for the draw order of the verices (will get texture and normal here too)
	while(!loader.eof())
	{	
		// If the input is a face (rather than a side/texture/etc.)
		if(input == 'f' && loader.peek() == ' ')
		{
			// Create indices component to get face data
			for(int i=0; i < 3; i++)
			{
				// Get the vertex numbers (position, texture, normal) to use and in what order
				// Subtract 1 since directx indices require to start at 0 but .obj starts at 1
				loader >> data;
				data--;
				model[8].push_back(data);
				input = loader.get();
				
				loader >> data;
				data--;
				model[9].push_back(data);
				input = loader.get();
				
				loader >> data;
				data--;
				model[10].push_back(data);
			}
		}

		input = loader.get();
	}

	loader.close();
}

void FileIO::LoadFont(string fontFile, vector<float>* const& font, char characters[])
{
	char input;
	float data;

	loader.open(fontFile);

	int count = 0;
	// Go through all positions and assign
	while(!loader.eof())
	{
		loader >> data;
		font[0].push_back(data);

		input = loader.get();
		input = loader.get();
		characters[count] = input;

		input = loader.get();
		loader >> data;
		font[1].push_back(data);
		input = loader.get();
		loader >> data;
		font[2].push_back(data);
		input = loader.get();
		loader >> data;
		font[3].push_back(data);

		count++;
	}
}
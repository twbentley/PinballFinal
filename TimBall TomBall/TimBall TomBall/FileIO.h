////////////////////////////////////////////////////////////////////////////////
// Filename: FileIO.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _FILEIO_H_
#define _FILEIO_H_

//////////////
// INCLUDES //
//////////////
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class FileIO
{
public:
	FileIO();
	FileIO(const FileIO&);
	~FileIO();

	static void LoadObject(string, vector<float>* const&);
	static void LoadFont(string, vector<float>* const&, char[]);

private:
	static ifstream loader;
};

#endif
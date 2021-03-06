#include "ColorShader.h"

using namespace std;
#include <iostream>

// Color Shader Constructor - load shader program
ColorShader::ColorShader()
{
	// Load shaders and use the resulting shader program    
	shaderProgram = InitShader( "vshader.glsl", "fshader.glsl" );
	glUseProgram( shaderProgram );
}

// Destructor
ColorShader::~ColorShader() { }

// Set the correct shader program to be used
void ColorShader::SetShader()
{
	glUseProgram(shaderProgram);
}

// Create a NULL-terminated string by reading the provided file
char* ColorShader::readShaderSource(const char* shaderFile)
{
	FILE* fp = fopen(shaderFile, "r"); // VS gives warning about being insecure :-)

    // one way to deal with warning: http://stackoverflow.com/questions/2575116/fopen-fopen-s-and-writing-to-files:
    /*FILE* fp;
    #ifdef WIN32
        errno_t err;
        if( (err  = fopen_s( &fp, shaderFile, "r" )) !=0 ) {
    #else
        if ((fp_config = fopen(shaderFile, "r")) == NULL) {
    #endif
        fprintf(stderr, "Cannot open config file %s!\n", shaderFile);
    }*/

	// Make sure the file is loaded correctly
    if ( fp == NULL ) { return NULL; }

	// Get the size of the file
    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);

	// Get the data from the file
    fseek(fp, 0L, SEEK_SET);
    char* buf = new char[size + 1];
    fread(buf, 1, size, fp);

	// Cap off the char array with a null-term
	fclose(fp);
	for(int i = size; i >= 0; i--)
	{
		if(buf[i] == '}')
		{
			 buf[i + 1] = '\0';
			 i = -1;
		}
	}

    return buf;
}

// Create a GLSL program object from vertex and fragment shader files
GLuint ColorShader::InitShader(const char* vShaderFile, const char* fShaderFile)
{
	// Shader struct, return an array of 2 shaders
	struct Shader
	{
		const char*  filename;
		GLenum       type;
		GLchar*      source;
    }
	shaders[2] =
		{
			{ vShaderFile, GL_VERTEX_SHADER, NULL },
			{ fShaderFile, GL_FRAGMENT_SHADER, NULL }
		};

	// Create the program for the shaders
    GLuint program = glCreateProgram();
   
    for ( int i = 0; i < 2; ++i ) 
	{
		// Get the shader file (read it)
		Shader& s = shaders[i];
		s.source = readShaderSource( s.filename );

		// Exit program if failed to read file
		if ( shaders[i].source == NULL ) 
		{ 
			exit( EXIT_FAILURE ); 
		}
		
		// Create the shader from source and compile
		GLuint shader = glCreateShader( s.type );
		glShaderSource( shader, 1, (const GLchar**) &s.source, NULL );
		glCompileShader( shader );

		// Check if shader compiled
		GLint  compiled;
		glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
		// If failed to compile - recompile, get error message, and exit
		if ( !compiled )
		{
			GLint  logSize;
			glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
			char* logMsg = new char[logSize];
			glGetShaderInfoLog( shader, logSize, NULL, logMsg );
			delete [] logMsg;

			exit( EXIT_FAILURE );
		}

		// Clean up memory
		delete [] s.source;

		// Attach the created shader to the program
		glAttachShader( program, shader );
    }

    // Link and error check
    glLinkProgram(program);

	// Link shader program
    GLint  linked;
    glGetProgramiv( program, GL_LINK_STATUS, &linked );
	// If failed to link, relink, get error message, and exit
    if ( !linked )
	{
		GLint  logSize;
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
		char* logMsg = new char[logSize];
		glGetProgramInfoLog( program, logSize, NULL, logMsg );
		delete [] logMsg;

		exit( EXIT_FAILURE );
    }

    // Use this program object
    glUseProgram(program);

    return program;
}

// Render the scene using the shaders
void ColorShader::Render(Matrix4* worldMatrix, Matrix4* viewMatrix, Matrix4* projectionMatrix, int indexCount, Vector4 color)
{
	// Set the shader and draw all elements using triangles
	SetShader();
	SetShaderParameters(worldMatrix, viewMatrix, projectionMatrix, color);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
}

// Set up the shader and matrices for a game object (vertex array must be swapped to the currect object)
void ColorShader::SetShaderParameters(Matrix4* worldMatrix, Matrix4* viewMatrix, Matrix4* projectionMatrix, Vector4 color)
{
	// Initialize the vertex position attribute from the vertex shader
	GLuint loc = glGetAttribLocation( shaderProgram, "vPosition" );
	glEnableVertexAttribArray( loc );

	// Define vertex attribute data
	glVertexAttribPointer( loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	// glUniformMatrix4fv should have GL_TRUE to enable transpose (our matrices are column-ordered)

	unsigned int location;

	// Set the world matrix in the vertex shader.
	location = glGetUniformLocation(shaderProgram, "worldMatrix");
	if(location == -1)
	{
		int x = 0;
	}
	glUniformMatrix4fv(location, 1, GL_TRUE, (GLfloat*)worldMatrix);

	// Set the view matrix in the vertex shader.
	location = glGetUniformLocation(shaderProgram, "viewMatrix");
	if(location == -1)
	{
		int x = 0;
	}
	glUniformMatrix4fv(location, 1, GL_TRUE, (GLfloat*)viewMatrix);

	// Set the projection matrix in the vertex shader.
	location = glGetUniformLocation(shaderProgram, "projectionMatrix");
	if(location == -1)
	{
		int x = 0;
	}
	glUniformMatrix4fv(location, 1, GL_TRUE, (GLfloat*)projectionMatrix);

	// Set the color in the shaders
	glGetUniformLocation(shaderProgram, "vColor");
	glUniform4f(shaderProgram, color.x, color.y, color.z, color.w);
}
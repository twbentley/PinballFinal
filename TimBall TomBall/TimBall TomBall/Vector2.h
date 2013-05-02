#ifndef VECTOR2_H
#define VECTOR2_H

#include <GL/glew.h>
#include <GL/glfw.h>
#include <istream>

using namespace std;

class Vector2
{
public:
	// Fields
	GLfloat  x;
    GLfloat  y;

	// Constructors
	Vector2();
    Vector2( GLfloat x, GLfloat y );
    Vector2( const Vector2& v );

	// Destructor
	~Vector2(void);

	// Copy assignment
	Vector2& operator = (const Vector2& other);

	// Indexers
	GLfloat& operator [] ( int i );
    const GLfloat operator [] ( int i ) const;
	
	// Non-Modifying Arithmatic Operator Overloads
	Vector2 operator - () const;
    Vector2 operator + ( const Vector2& v ) const;
    Vector2 operator - ( const Vector2& v ) const;
    Vector2 operator * ( const GLfloat s ) const;
    Vector2 operator * ( const Vector2& v ) const;
    friend Vector2 operator * ( const GLfloat s, const Vector2& v );
	Vector2 operator / ( const GLfloat s ) const;

	// Modifying Arithmatic Operator Overloads
	Vector2& operator += ( const Vector2& v );
    Vector2& operator -= ( const Vector2& v );
    Vector2& operator *= ( const GLfloat s );
    Vector2& operator *= ( const Vector2& v );
    Vector2& operator /= ( const GLfloat s );

	// double cast overload
	operator double();

	// Non-class Vector2 Methods
	GLfloat dot( const Vector2& v ) const;
	GLfloat length( ) const;
	Vector2 normalize( ) const;
};

#endif
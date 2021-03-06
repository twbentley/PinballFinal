#ifndef Vector3_H
#define Vector3_H

#include <GL/glew.h>
#include <GL/glfw.h>
#include <istream>

class Vector3
{
public:
	// Fields
	GLfloat x;
    GLfloat y;
	GLfloat z;

	// Constructors
	Vector3();
    Vector3(GLfloat x, GLfloat y, GLfloat z);
    Vector3(const Vector3& v);

	// Destructor
	~Vector3(void);

	// Copy assignment
	Vector3& operator = (const Vector3& other);

	// Indexers
	GLfloat& operator[](int i);
    const GLfloat operator[](int i) const;
	
	// Non-Modifying Arithmatic Operator Overloads
	Vector3 operator - () const;
    Vector3 operator + ( const Vector3& v ) const;
    Vector3 operator - ( const Vector3& v ) const;
    Vector3 operator * ( const GLfloat s ) const;
    Vector3 operator * ( const Vector3& v ) const;
	Vector3 operator / ( const GLfloat s ) const;

	// Modifying Arithmatic Operator Overloads
	Vector3& operator += ( const Vector3& v );
    Vector3& operator -= ( const Vector3& v );
    Vector3& operator *= ( const GLfloat s );
    Vector3& operator *= ( const Vector3& v );
    Vector3& operator /= ( const GLfloat s );

	// Non-class Vector3 Methods
	GLfloat dot( const Vector3& u, const Vector3& v ) const;
	GLfloat length( const Vector3& v ) const;
	Vector3 normalize( const Vector3& v ) const;
	Vector3 cross(const Vector3& a, const Vector3& b) const;
};

#endif
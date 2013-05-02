// Based off of Angel's vec2 functionality

#include "Vector2.h"

// Default Constructor
Vector2::Vector2()
{
	x = 0;
	y = 0;
}

// Parameterized Constructor
Vector2::Vector2(GLfloat px, GLfloat py)
{
	x = px;
	y = py;
}

// Copy Constructor
Vector2::Vector2(const Vector2& v)
{
	x = v.x;
	y = v.y;
}

// Destructor
Vector2::~Vector2() { }

// Copy assignment
Vector2& Vector2::operator=(const Vector2& other)
{
	x = other.x;
	y = other.y;
	return *this;
}

// Indexers (make safer?)
GLfloat& Vector2::operator[](int i)
{
	return *(&x + i);
}
const GLfloat Vector2::operator[](int i) const
{
	return *(&x + i);
}

// Vector value negation operator (return Vector using new values)
Vector2 Vector2::operator - () const
{
	return Vector2( -x, -y);
}
// Vector-Vector addition operator (return Vector using new values)
Vector2 Vector2::operator + ( const Vector2& v ) const
{
	return Vector2( x + v.x, y + v.y);
}
// Vector-Vector subtraction operator (return Vector using new values)
Vector2 Vector2::operator - ( const Vector2& v ) const
{
	return Vector2(x - v.x, y - v.y);
}
// Vector-scalar multiplication operator (return Vector using new values)
Vector2 Vector2::operator * ( const GLfloat s ) const
{
	return Vector2(s * x, s * y);
}
// Vector-Vector multiplication operator (return Vector using new values)
Vector2 Vector2::operator * ( const Vector2& v ) const
{
	return Vector2(v.x * x, v.y * y);
}
// Vector-scalar division operator
Vector2 Vector2::operator / ( const GLfloat s ) const
{
	GLfloat temp = GLfloat(1.0) / s;
	return *this * temp;
}

// Vector-Vector addition applied to this object
Vector2& Vector2::operator += ( const Vector2& v )
{ 
	x += v.x;  y += v.y;  return *this; 
}
// Vector-Vector subtraction applied to this object
Vector2& Vector2::operator -= ( const Vector2& v )
{ 
	x -= v.x;  y -= v.y;  return *this; 
}
// Vector-scalar multiplication applied to this object
Vector2& Vector2::operator *= ( const GLfloat s )
{ 
	x *= s;  y *= s;  return *this; 
}
// Vector-Vector multiplication applied to this object
Vector2& Vector2::operator *= ( const Vector2& v )
{ 
	x *= v.x;  y *= v.y;  return *this; 
}
// Vector-scalar division applied to this object
Vector2& Vector2::operator /= ( const GLfloat s )
{
	GLfloat r = GLfloat(1.0) / s;
	*this *= r;

	return *this;
}

// Vector-Vector dot product
GLfloat Vector2::dot( const Vector2& v ) const
{
	return x*v.x + y*v.y;
}
// Vector length
GLfloat Vector2::length( ) const
{
	return std::sqrt(dot(*this));
}
// Vector normalize
Vector2 Vector2::normalize( ) const
{
	return *this / length();
}

 
Vector2::operator double()
{
	return length();
}
#ifndef MATRIX2_H
#define MATRIX2_H

#include "Vector2.h"
#include <string>
#include <sstream>
//#include <ostream>
//#include <istream>

class Matrix2
{
public:
	Vector2 matrix[2];

	// Constructors and Destructor
	Matrix2(void);
	Matrix2::Matrix2(const Vector2& a, const Vector2& b);
	Matrix2(GLfloat m00, GLfloat m01, GLfloat m10, GLfloat m11);
	Matrix2(const Matrix2& m);
	~Matrix2(void);

	// Indexers
	Vector2& operator [] ( int i );
	const Vector2& operator [] ( int i ) const;

	// Non-Modifying Arithmatic Operators
	Matrix2 operator + (const Matrix2& m) const;
	Matrix2 operator - (const Matrix2& m) const;
	Matrix2 operator * (const GLfloat s) const;
	Matrix2 operator * (const Matrix2& m) const;
	friend Matrix2 operator * (const GLfloat s, const Matrix2& m);
	Matrix2 operator / (const GLfloat s) const;

	// Modifying Arithmatic Operators
	Matrix2& operator += (const Matrix2& m);
	Matrix2& operator -= (const Matrix2& m);
	Matrix2& operator *= (const GLfloat s);
	Matrix2& operator *= (const Matrix2& m);
	Matrix2& operator /= (const GLfloat s);

	// Matrix/Vector Operator
	Vector2 operator * (const Vector2& v) const;

	// Insertion and Extraction Operators
	//friend ostream& operator << ( ostream& os, const Matrix2& m);
	//friend istream& operator >> (istream& is, Matrix2& m);

	// Conversion Operators
	operator const GLfloat* () const;
	operator GLfloat* ();

	// Non-Class Matrix2 Methods
	Matrix2 matrixCompMult(const Matrix2& A, const Matrix2& B);
	Matrix2 transpose();

	string ToString();
};

#endif
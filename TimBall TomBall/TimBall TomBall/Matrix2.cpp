#include "Matrix2.h"

// Default Constructor (Diagonal/Identity) Matrix
Matrix2::Matrix2(void)
{
	matrix[0].x = 1.0f;
	matrix[1].y = 1.0f;
}

Matrix2::Matrix2(const Vector2& a, const Vector2& b)
{
	matrix[0] = a;
	matrix[1] = b;
}

// Full Parameterized Constructor
Matrix2::Matrix2(GLfloat m00, GLfloat m01, GLfloat m10, GLfloat m11)
{
	matrix[0] = Vector2(m00, m01);
	matrix[1] = Vector2(m10, m11);
}

// Copy Constructor
Matrix2::Matrix2(const Matrix2& m)
{
	matrix[0] = m.matrix[0];
	matrix[1] = m.matrix[1];
}

// Destructor
Matrix2::~Matrix2(void)
{
}

// Indexer operators
Vector2& Matrix2::operator [] (int i)
{ return matrix[i]; }
const Vector2& Matrix2::operator [] (int i) const
{ return matrix[i]; }

// Matrix-Matrix addition (non-modifying)
Matrix2 Matrix2::operator + (const Matrix2& m) const
{
	return Matrix2
	(
		matrix[0] + m.matrix[0],
		matrix[1] + m.matrix[1]
	);
}

// Matrix-Matrix subtraction (non-modifying)
Matrix2 Matrix2::operator - (const Matrix2& m) const
{
	return Matrix2
	(
		matrix[0] - m.matrix[0],
		matrix[1] - m.matrix[1]
	);
}

// Matrix-Scalar multiplication (non-modifying)
Matrix2 Matrix2::operator * (const GLfloat s) const
{
	return Matrix2
	(
		matrix[0] * s,
		matrix[1] * s
	);
}

// Matrix-Matrix multiplication (non-modifying)
Matrix2 Matrix2::operator * (const Matrix2& m) const
{
	Matrix2 a(0, 0, 0, 0);

	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			for(int k = 0; k < 2; k++)
			{
				a[i][j] += matrix[i][k] * m.matrix[k][j];	// <-- is this right? (m.matrix[][] instead of m[][])
				//a[i][j] += _m[i][k] * m[k][j];
			}
		}
	}

	return a;
}

// Matrix-Scalar division (non-modifying)
Matrix2 Matrix2::operator / (const GLfloat s) const
{
	// Don't forget about divide-by-zero

	GLfloat r = GLfloat(1.0) / s;
	return *this * r;
	//Why not: 'return *this / s;' ?
}

// Matrix-Matrix addition (modifying)
Matrix2& Matrix2::operator += (const Matrix2& m)
{
	matrix[0] += m.matrix[0];
	matrix[1] += m.matrix[1];

	return *this;
}

// Matrix-Matrix subtraction (modifying)
Matrix2& Matrix2::operator -= (const Matrix2& m)
{
	matrix[0] -= m.matrix[0];
	matrix[1] -= m.matrix[1];

	return *this;
}

// Matrix-Scalar multiplication (modifying)
Matrix2& Matrix2::operator *= (const GLfloat s)
{
	matrix[0] *= s;
	matrix[1] *= s;

	return *this;
}

// Matrix-Matrix multiplication (modifying)
Matrix2& Matrix2::operator *= (const Matrix2& m)
{
	// Initialize a temporary Matrix2 to be initialized with the new values
	Matrix2 a(0.0f, 0.0f, 0.0f, 0.0f);

	// Perform matrix(2x2) multiplication and store in temp matrix
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			for(int k = 0; k < 2; k++)
			{
				a[i][j] += matrix[i][k] * m.matrix[k][j];
			}
		}
	}

	// Point this matrix at the new one (with new values)
	return *this = a;
}

// Matrix-Scalar division (modifying)
Matrix2& Matrix2::operator /= (const GLfloat s)
{
	GLfloat r = GLfloat(1.0) / s;
	return *this *= r;
}

// Matrix-Row multiplication (non-modifying)
Vector2 Matrix2::operator * (const Vector2& v) const
{
	return
	(
		Vector2
		(
			matrix[0][0] * v.x + matrix[0][1] * v.y,
			matrix[1][0] * v.x + matrix[1][1] * v.y
		)
	);
}

// What are these for?
Matrix2::operator const GLfloat* () const
{
	return static_cast<const GLfloat*>( &matrix[0].x );
}
Matrix2::operator GLfloat* () 
{
	return static_cast<GLfloat*>( &matrix[0].x );
}

// Not sure what this actually is
Matrix2 matrixCompMult(const Matrix2& A, const Matrix2& B)
{
	return Matrix2
	(
		A.matrix[0][0] * B.matrix[0][0],
		A.matrix[0][1] * B.matrix[0][1],
		A.matrix[1][0] * B.matrix[1][0],
		A.matrix[1][1] * B.matrix[1][1]
	);
}

// Transpose the given matrix (non-modifying)
Matrix2 Matrix2::transpose()
{
	return Matrix2( matrix[0][0], matrix[1][0], matrix[0][1], matrix[1][1] );
}

// Return a string version of the Matrix
string Matrix2::ToString()
{
	ostringstream stream;

	for(int i = 0; i < 2; i++)
	{
		stream << "| ";
		stream << matrix[i].x;
		stream << " ";
		stream << matrix[i].y;
		stream << " |";
		stream << endl;
	}

	return stream.str();
}
#include "Matrix.h"

void Matrixf::Matrix3f::setPointer ( )
{
	int index = 0;
	for ( int i = 0; i < counter; i++ )
	{
		for ( int j = 0; i < counter; j++ )
		{
			index++;
			pointer [ index ] = mat [ i ] [ j ];
		}
	}
}

void Matrixf::Matrix4f::setPointer ( )
{
	int index = 0;
	for ( int i = 0; i < counter; i++ )
	{
		for ( int j = 0; i < counter; j++ )
		{
			index++;
			pointer [ index ] = mat [ i ] [ j ];
		}
	}
}

Matrixf::Matrix4f::Matrix4f ( )
{
	counter = 4;
	mat = new float*[4];
	
	for ( int  i = 0; i < counter; ++i )
	{
	    mat[i] = new float[4];
	}

	for ( int i = 0; i < counter; i++ )
	{
		for ( int j = 0; i < counter; j++ )
		{
			mat [ i ] [ j ] = 0;
		}
	}

	setPointer ( );
}

Matrixf::Matrix4f::Matrix4f ( float** values )
{
	for ( int i = 0; i < counter; i++ )
	{
		for ( int j = 0; i < counter; j++ )
		{
			mat [ i ] [ j ] = values [ i ] [ j ];
		}
	}
	setPointer ( );
}

Matrixf::Matrix4f::Matrix4f ( float f0, float f1, float f2, float f3,
					 float s0, float s1, float s2, float s3,
					 float t0, float t1, float t2, float t3,
					 float fi0, float fi1, float fi2, float fi3 )
{
	counter = 0;
	mat [ 0 ] [ 0 ] = f0; 
	mat [ 1 ] [ 0 ] = s0;
	mat [ 2 ] [ 0 ] = t0;
	mat [ 3 ] [ 0 ] = fi0;

    mat [ 0 ] [ 1 ] = f1;
	mat [ 1 ] [ 1 ] = s1;
	mat [ 2 ] [ 1 ] = t1;
	mat [ 3 ] [ 1 ] = fi1;

	mat [ 0 ] [ 2 ] = f2;
	mat [ 1 ] [ 2 ] = s2;
	mat [ 2 ] [ 2 ] = t2;
	mat [ 3 ] [ 2 ] = fi2;

	mat [ 0 ] [ 3 ] = f3;
	mat [ 1 ] [ 3 ] = s3;
	mat [ 2 ] [ 3 ] = t3;
	mat [ 3 ] [ 3 ] = fi3;

	setPointer ( );
}

Matrixf::Matrix4f::~Matrix4f ( )
{
	for ( int i = 0; i < counter; ++i)
	{
		delete [] mat[i];
	}

	delete [] mat;
	delete [] pointer;
}

void Matrixf::Matrix4f::negate ( )
{
	for ( int i = 0; i < counter; i++ )
	{
		for ( int j = 0; i < counter; j++ )
		{
			mat [ i ] [ j ] = -mat [ i ] [ j ];
		}
	}
}

void Matrixf::Matrix4f::setColumn ( int collumn, float value )
{
	for ( int i = 0; i < counter; i++ )
	{
		mat [ i ] [ collumn ] = value;
	}
}

void Matrixf::Matrix4f::setRow ( int row, float value )
{
	for ( int i = 0; i < counter; i++ )
	{
		mat [ row ] [ i ] = value;
	}
}

void Matrixf::Matrix4f::setXY ( int x, int y, float value )
{
	mat [ x ] [ y ] = value;
}

Matrixf::Matrix4f Matrixf::Matrix4f::operator*  ( Matrix4f& m )
{
	Matrix4f matrix;

	for ( int i = 0; i < counter; i++ )
	{
		for ( int j = 0; j < 4; j++ )
		{
			for ( int k = 0; k < 4; k ++ ) 
			{
				matrix.mat [ i ] [ j ] += m.mat [ i ] [ k ] * mat [ k ] [ j ]; 
			}
		}
	}

	return matrix;
}

bool Matrixf::Matrix4f::operator== ( Matrix4f& m )
{
	for ( int i = 0; i < counter; i++ )
	{
		for ( int j = 0; j < 4; j++ )
		{
			if ( mat [ i ] [ j ] != m.mat [ i ] [ j ] )
				return false;
		}
	}

	return true;
}

void Matrixf::Matrix4f::operator= ( Matrix4f& matrix )
{
	for ( int i = 0; i < counter; i++ )
	{
		for ( int j = 0; j < 4; j++ )
		{
			mat [ i ] [ j ] = matrix.mat [ i ] [ j ];	
		}
	}
}

Matrixf::Matrix4f Matrixf::Matrix4f::operator+ ( Matrix4f& m )
{
	Matrix4f maty;
	
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			maty.mat[i][j] = mat[i][j] + m.mat[i][j];
		}
	}
	return maty;
}

Matrixf::Matrix4f Matrixf::Matrix4f::operator- ( Matrix4f& m )
{
	Matrix4f maty;
	
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			maty.mat[i][j] = mat[i][j] - m.mat[i][j];
		}
	}
	return maty;
}

Matrixf::Matrix3f::Matrix3f ( )
{
	counter = 4;
	mat = new float*[4];
	
	for ( int  i = 0; i < counter; ++i )
	{
	    mat[i] = new float[4];
	}

	for ( int i = 0; i < counter; i++ )
	{
		for ( int j = 0; i < counter; j++ )
		{
			mat [ i ] [ j ] = 0;
		}
	}
}

Matrixf::Matrix3f::Matrix3f ( float** values )
{
	for ( int i = 0; i < counter; i++ )
	{
		for ( int j = 0; i < counter; j++ )
		{
			mat [ i ] [ j ] = values [ i ] [ j ];
		}
	}
}

Matrixf::Matrix3f::Matrix3f ( float f0, float f1, float f2, float f3,
					 float s0, float s1, float s2, float s3,
					 float t0, float t1, float t2, float t3 )
{
	counter = 0;
	mat [ 0 ] [ 0 ] = f0; 
	mat [ 1 ] [ 0 ] = s0;
	mat [ 2 ] [ 0 ] = t0;

    mat [ 0 ] [ 1 ] = f1;
	mat [ 1 ] [ 1 ] = s1;
	mat [ 2 ] [ 1 ] = t1;

	mat [ 0 ] [ 2 ] = f2;
	mat [ 1 ] [ 2 ] = s2;
	mat [ 2 ] [ 2 ] = t2;

	mat [ 0 ] [ 3 ] = f3;
	mat [ 1 ] [ 3 ] = s3;
	mat [ 2 ] [ 3 ] = t3;
}

Matrixf::Matrix3f::~Matrix3f ( )
{
	for ( int i = 0; i < counter; ++i)
	{
		delete [] mat[i];
	}

	delete [] mat;
}

void Matrixf::Matrix3f::negate ( )
{
	for ( int i = 0; i < counter; i++ )
	{
		for ( int j = 0; i < counter; j++ )
		{
			mat [ i ] [ j ] = -mat [ i ] [ j ];
		}
	}
}

void Matrixf::Matrix3f::setColumn ( int collumn, float value )
{
	for ( int i = 0; i < counter; i++ )
	{
		mat [ i ] [ collumn ] = value;
	}
}

void Matrixf::Matrix3f::setRow ( int row, float value )
{
	for ( int i = 0; i < counter; i++ )
	{
		mat [ row ] [ i ] = value;
	}
}

void Matrixf::Matrix3f::setXY ( int x, int y, float value )
{
	mat [ x ] [ y ] = value;
}

Matrixf::Matrix3f Matrixf::Matrix3f::operator*  ( Matrix3f& m )
{
	Matrix3f matrix;

	for ( int i = 0; i < counter; i++ )
	{
		for ( int j = 0; j < 4; j++ )
		{
			for ( int k = 0; k < 4; k ++ ) 
			{
				matrix.mat [ i ] [ j ] += m.mat [ i ] [ k ] * mat [ k ] [ j ]; 
			}
		}
	}

	return matrix;
}

bool Matrixf::Matrix3f::operator== ( Matrix3f& m )
{
	for ( int i = 0; i < counter; i++ )
	{
		for ( int j = 0; j < 4; j++ )
		{
			if ( mat [ i ] [ j ] != m.mat [ i ] [ j ] )
				return false;
		}
	}

	return true;
}

void Matrixf::Matrix3f::operator= ( Matrix3f& matrix )
{
	for ( int i = 0; i < counter; i++ )
	{
		for ( int j = 0; j < 4; j++ )
		{
			mat [ i ] [ j ] = matrix.mat [ i ] [ j ];	
		}
	}
}

Matrixf::Matrix3f Matrixf::Matrix3f::operator+ ( Matrix3f& m )
{
	Matrix3f maty;
	
	for ( int i = 0; i < counter; i++ )
	{
		for ( int j = 0; j < counter; j++ )
		{
			maty.mat[i][j] = mat[i][j] + m.mat[i][j];
		}
	}
	return maty;
}

Matrixf::Matrix3f Matrixf::Matrix3f::operator- ( Matrix3f& m )
{
	Matrix3f maty;
	
	for ( int i = 0; i < counter; i++)
	{
		for (int j=0; j < counter; j++)
		{
			maty.mat[i][j] = mat[i][j] - m.mat[i][j];
		}
	}
	return maty;
}

float* Matrixf::Matrix4f::getPointer ( )
{
	return pointer;
}

float* Matrixf::Matrix3f::getPointer ( )
{
	return pointer;
}

float Matrixf::Matrix3f::getXY ( int x, int y )
{
	return mat [ x ] [ y ];
}

float Matrixf::Matrix4f::getXY ( int x, int y )
{
	return mat [ x ] [ y ];
}
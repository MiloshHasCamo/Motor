#ifndef MATRIX_H_
#define MATRIX_H_

namespace Matrixf
{
	class Matrix4f
	{
	private:
		unsigned short int counter;
		float* pointer;

		void setPointer ( );
	public:
		float** mat;
	
		Matrix4f  ( void );
		Matrix4f  ( float** values );
	
		Matrix4f  ( float f0, float f1, float f2, float f3,
				    float s0, float s1, float s2, float s3,
					float t0, float t1, float t2, float t3,
					float fi0, float fi1, float fi2, float fi3 );
	
		~Matrix4f ( );
	
		void setRow    ( int Row, float value );
		void setColumn ( int column, float value );
		void setXY     ( int x, int y, float value );
		void negate    ( void );

		float  getXY      ( int x, int y );
		float* getPointer ( );
	
		Matrix4f operator*  ( Matrix4f& );
		bool     operator== ( Matrix4f& );
		void     operator=  ( Matrix4f& );
		Matrix4f operator+  ( Matrix4f& );
		Matrix4f operator-  ( Matrix4f& );
	};

	class Matrix3f
	{
	private:
		unsigned short int counter;
		float* pointer;
		
		void setPointer ( );
	public:
		float** mat;
	
		Matrix3f  ( void );
		Matrix3f  ( float** values );
	
		Matrix3f  ( float f0, float f1, float f2, float f3,
				    float s0, float s1, float s2, float s3,
					float t0, float t1, float t2, float t3 );
	
		~Matrix3f ( );
	
		void setRow     ( int Row, float value );
		void setColumn  ( int column, float value );
		void setXY      ( int x, int y, float value );

		float  getXY      ( int x, int y );
		float* getPointer ( );

		void negate     ( void );
	
		Matrix3f operator*  ( Matrix3f& );
		bool     operator== ( Matrix3f& );
		void     operator=  ( Matrix3f& );
		Matrix3f operator+  ( Matrix3f& );
		Matrix3f operator-  ( Matrix3f& );
	};
}

#endif//MATRIX_H_
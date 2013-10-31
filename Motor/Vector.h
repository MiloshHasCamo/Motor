#ifndef VECTOR_H_
#define VECTOR_H_

#include <math.h>
#include <iostream>

using namespace std;

namespace Vectorf
{
	class Vector2f
	{
	private:
		float x, y;
	
	public:
		Vector2f ( );
		Vector2f ( float x, float y );
		
		float Length ( );
		float Dot ( Vector2f r );
		Vector2f* Normalize ( );
	
		Vector2f& operator + ( Vector2f& other );
		Vector2f& operator + ( float other );
		Vector2f& operator - ( Vector2f& other );
		Vector2f& operator - ( float other );
		Vector2f& operator * ( Vector2f& other );
		Vector2f& operator * ( float other );
		Vector2f& operator / ( Vector2f& other );
		Vector2f& operator / ( float other );
		Vector2f* Abs ( );
	
		float getX ( );
		float getY ( );
		void  setX ( float x );
		void  setY ( float y );
	
		string toString ( );
	};

	class Vector3f
	{
	private:
		float x, y, z;
	
	public:
		Vector3f ( );
		Vector3f ( float x, float y, float z );
		
		float Length ( );
		float Dot ( Vector3f r );
		Vector3f* Cross ( Vector3f r );
		Vector3f* Normalize ( );
			  
		Vector3f& operator + ( Vector3f& other );
		Vector3f& operator + ( float other );
		Vector3f& operator - ( Vector3f& other );
		Vector3f& operator - ( float other );
		Vector3f& operator * ( Vector3f& other );
		Vector3f& operator * ( float other );
		Vector3f& operator / ( Vector3f& other );
		Vector3f& operator / ( float other );
		Vector3f* Abs ( );
	
		float getX ( ) const ;
		float getY ( ) const ;
		float getZ ( ) const ;
		void  setX ( float x );
		void  setY ( float y );
		void  setZ ( float z );
	
		string toString ( );
	};
} 

#endif//VECTOR_H_
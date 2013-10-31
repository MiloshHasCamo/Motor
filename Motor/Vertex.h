#ifndef VERTEX_H_
#define VERTEX_H_

#include <iostream>
#include <stdlib.h>
#include "Vector.h"

#define SIZE_VERTEX 8

using namespace Vectorf;

namespace Vertexf
{
	class Vertex2f
	{
	private:
		Vector2f pos;
		Vector2f TextureCoordinate;
		Vector2f Normal;

	public:
		Vertex2f ( );
		Vertex2f ( Vector2f pos );
		Vertex2f ( Vector2f pos, Vector2f TextureCoordinate );
		Vertex2f ( Vector2f pos, Vector2f TextureCoordinate, Vector2f normal );

		Vector2f getPosition ( );
		Vector2f getTextureCoordinate ( );
		Vector2f getNormal ( );

		void setPosition ( Vector2f pos );
		void setNormal   ( Vector2f normal );
		void setTextureCoordinate ( Vector2f TextureCoordinate );
	};

	class Vertex3f 
	{
		private:
		Vector3f pos;
		Vector2f TextureCoordinate;
		Vector3f Normal;

	public:
		Vertex3f ( Vector3f pos );
		Vertex3f ( Vector3f pos, Vector2f TextureCoordinate );
		Vertex3f ( Vector3f pos, Vector2f TextureCoordinate, Vector3f normal );

		Vector3f getPosition ( );
		Vector2f getTextureCoordinate ( );
		Vector3f getNormal ( );

		void setPosition ( Vector3f pos );
		void setNormal   ( Vector3f normal );
		void setTextureCoordinate ( Vector2f TextureCoordinate );
	};
}

#endif//VERTEX_H_
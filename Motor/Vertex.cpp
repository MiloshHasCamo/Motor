#include "Vertex.h"

Vertexf::Vertex3f::Vertex3f ( Vector3f _pos )
{
	pos = _pos;
	TextureCoordinate = Vector2f ( 0, 0 );
	Normal = Vector3f ( 0, 0, 0 );
}

Vertexf::Vertex3f::Vertex3f ( Vector3f _pos, Vector2f _texcord )
{
	pos = _pos;
	TextureCoordinate = _texcord;
	Normal = Vector3f ( 0, 0, 0 );
}

Vertexf::Vertex3f::Vertex3f ( Vector3f _pos, Vector2f _texcord, Vector3f normal )
{
	pos = _pos;
	TextureCoordinate = _texcord;
	Normal = normal;
}

Vector3f Vertexf::Vertex3f::getNormal ( )
{
	return Normal;
}

Vector3f Vertexf::Vertex3f::getPosition ( )
{
	return pos;
}

Vector2f Vertexf::Vertex3f::getTextureCoordinate ( )
{
	return TextureCoordinate;
}

void Vertexf::Vertex3f::setNormal ( Vector3f r )
{
	Normal = r;
}

void Vertexf::Vertex3f::setPosition ( Vector3f p )
{
	pos = p;
}

void Vertexf::Vertex3f::setTextureCoordinate ( Vector2f tc )
{
	TextureCoordinate = tc;
}

Vertexf::Vertex2f::Vertex2f ( Vector2f _pos )
{
	pos = _pos;
	TextureCoordinate = Vector2f ( 0, 0 );
	Normal = Vector2f ( 0, 0 );
}

Vertexf::Vertex2f::Vertex2f ( Vector2f _pos, Vector2f _texcord )
{
	pos = _pos;
	TextureCoordinate = _texcord;
	Normal = Vector2f ( 0, 0 );
}

Vertexf::Vertex2f::Vertex2f ( Vector2f _pos, Vector2f _texcord, Vector2f normal )
{
	pos = _pos;
	TextureCoordinate = _texcord;
	Normal = normal;
}

Vector2f Vertexf::Vertex2f::getNormal ( )
{
	return Normal;
}

Vector2f Vertexf::Vertex2f::getPosition ( )
{
	return pos;
}

Vector2f Vertexf::Vertex2f::getTextureCoordinate ( )
{
	return TextureCoordinate;
}

void Vertexf::Vertex2f::setNormal ( Vector2f r )
{
	Normal = r;
}

void Vertexf::Vertex2f::setPosition ( Vector2f p )
{
	pos = p;
}

void Vertexf::Vertex2f::setTextureCoordinate ( Vector2f tc )
{
	TextureCoordinate = tc;
}
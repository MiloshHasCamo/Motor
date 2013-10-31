#include "Vector.h"

#pragma warning ( disable: 4244 )
#pragma warning ( disable: 4172 )

Vectorf::Vector2f::Vector2f ( )
{
	x = y = 0;
}

Vectorf::Vector2f::Vector2f ( float _x, float _y )
{
	x = _x;
	y = _y;
}

float Vectorf::Vector2f::Length ( )
{
	return ( float ) sqrt ( x * x + y * y );
}

float Vectorf::Vector2f::Dot ( Vector2f r )
{
	return x * r.getX ( ) + y * r.getY ( );
}

Vectorf::Vector2f* Vectorf::Vector2f::Normalize ( )
{
	float length = Length ( );

	return new Vector2f ( x / length, y / length );
}

Vectorf::Vector2f& Vectorf::Vector2f::operator+ ( Vectorf::Vector2f& other )
{
	return Vector2f ( x + other.getX ( ), y + other.getY ( ) );
}

Vectorf::Vector2f& Vectorf::Vector2f::operator+ ( float other )
{
	return Vector2f ( x + other, y + other );
}

Vectorf::Vector2f& Vectorf::Vector2f::operator- ( Vectorf::Vector2f& other )
{
	return Vector2f ( x - other.getX ( ), y - other.getY ( ) );
}

Vectorf::Vector2f& Vectorf::Vector2f::operator- ( float other )
{
	return Vector2f ( x - other, y - other );
}

Vectorf::Vector2f& Vectorf::Vector2f::operator* ( Vectorf::Vector2f& other )
{
	return Vector2f ( x * other.getX ( ), y * other.getY ( ) );
}

Vectorf::Vector2f& Vectorf::Vector2f::operator* ( float other )
{
	return Vector2f ( x * other, y * other );
}

Vectorf::Vector2f& Vectorf::Vector2f::operator/ ( Vectorf::Vector2f& other )
{
	return Vector2f ( x / other.getX ( ), y / other.getY ( ) );
}

Vectorf::Vector2f& Vectorf::Vector2f::operator/ ( float other )
{
	return Vector2f ( x / other, y / other );
}

Vectorf::Vector2f* Vectorf::Vector2f::Abs ( )
{
	return new Vector2f ( abs ( x ), abs ( y ) );
}

string Vectorf::Vector2f::toString ( )
{
	string str;
	str += " ( ";
	str += x;
	str += ", ";
	str += y;
	str += " ) ";
	return str;
}

float Vectorf::Vector2f::getX ( )
{
	return x;
}

float Vectorf::Vector2f::getY ( )
{
	return y;
}

void Vectorf::Vector2f::setX ( float _x )
{
	x = _x;
}

void Vectorf::Vector2f::setY ( float _y )
{
	y = _y;
}

Vectorf::Vector3f::Vector3f ( )
{
	x = y = z = 0;
}

Vectorf::Vector3f::Vector3f ( float _x, float _y, float _z )
{
	x = _x;
	y = _y;
	z = _z;
}

float Vectorf::Vector3f::Length ( )
{
	return ( float ) sqrt ( x * x + y * y + z * z );
}

float Vectorf::Vector3f::Dot ( Vector3f r )
{
	return x * r.getX ( ) + y * r.getY ( ) + z * r.getZ ( );
}

Vectorf::Vector3f* Vectorf::Vector3f::Cross ( Vector3f r )
{
	float _x = y * r.getZ ( ) - z * r.getY ( );
	float _y = z * r.getX ( ) - x * r.getZ ( );
	float _z = x * r.getY ( ) - y * r.getX ( );

	return new Vector3f ( _x, _y, _z );
}

Vectorf::Vector3f* Vectorf::Vector3f::Normalize ( )
{
	float length = Length ( );

	return new Vector3f ( x / length, y / length, z / length );
}

Vectorf::Vector3f& Vectorf::Vector3f::operator+ ( Vectorf::Vector3f& other )
{
	return Vector3f ( x + other.getX ( ), y + other.getY ( ), z + other.getZ ( ) );
}

Vectorf::Vector3f& Vectorf::Vector3f::operator+ ( float other )
{
	return Vector3f ( x + other, y + other, z + other );
}

Vectorf::Vector3f& Vectorf::Vector3f::operator- ( Vectorf::Vector3f& other )
{
	return Vector3f ( x - other.getX ( ), y - other.getY ( ), z - other.getZ ( ) );
}

Vectorf::Vector3f& Vectorf::Vector3f::operator- ( float other )
{
	return Vector3f ( x - other, y - other, z - other );
}

Vectorf::Vector3f& Vectorf::Vector3f::operator* ( Vectorf::Vector3f& other )
{
	return Vector3f ( x * other.getX ( ), y * other.getY ( ), z * other.getZ ( ) );
}

Vectorf::Vector3f& Vectorf::Vector3f::operator* ( float other )
{
	return Vector3f ( x * other, y * other, z * other );
}

Vectorf::Vector3f& Vectorf::Vector3f::operator/ ( Vectorf::Vector3f& other )
{
	return Vector3f ( x / other.getX ( ), y / other.getY ( ), z / other.getZ ( ) );
}

Vectorf::Vector3f& Vectorf::Vector3f::operator/ ( float other )
{
	return Vector3f ( x / other, y / other, z / other );
}

Vectorf::Vector3f* Vectorf::Vector3f::Abs ( )
{
	return new Vector3f ( abs ( x ), abs ( y ), abs ( z ) );
}

string Vectorf::Vector3f::toString ( )
{
	string str;
	str += " ( ";
	str += x;
	str += ", ";
	str += y;
	str += ", ";
	str += z;
	str += " ) ";
	return str;
}

float Vectorf::Vector3f::getX ( ) const
{
	return x;
}

float Vectorf::Vector3f::getY ( ) const 
{
	return y;
}

float Vectorf::Vector3f::getZ ( ) const 
{
	return z;
}

void Vectorf::Vector3f::setX ( float _x )
{
	x = _x;
}

void Vectorf::Vector3f::setY ( float _y )
{
	y = _y;
}

void Vectorf::Vector3f::setZ ( float _z )
{
	z = _z;
}
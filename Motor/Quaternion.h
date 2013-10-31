#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "Vector.h"

struct Quaternion
{
	float x, y, z, w;

	Quaternion ( float _x, float _y, float _z, float _w )
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	void Normalize ( );
	Quaternion* Conjugate ( );

	Quaternion* operator* ( const Quaternion& r );
	Quaternion* operator* ( const Vectorf::Vector3f& v );
};

#endif//QUATERNION_H_
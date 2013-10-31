#include "Quaternion.h"
#include <math.h>

void Quaternion::Normalize ( )
{
	float length = sqrtf ( x * x + y * y + z * z + w * w );

	x /= length;
	y /= length;
	z /= length;
	w /= length;
}

Quaternion* Quaternion::Conjugate ( )
{
	Quaternion* ret = new Quaternion ( -x, -y, -z, w );
	return ret;
}

Quaternion* Quaternion::operator*(const Quaternion& r)
{
    const float _w = (w * r.w) - (x * r.x) - (y * r.y) - (z * r.z);
    const float _x = (x * r.w) + (w * r.x) + (y * r.z) - (z * r.y);
    const float _y = (y * r.w) + (w * r.y) + (z * r.x) - (x * r.z);
    const float _z = (z * r.w) + (w * r.z) + (x * r.y) - (y * r.x);

	Quaternion* ret = new Quaternion (_x, _y, _z, _w);

    return ret;
}

Quaternion* Quaternion::operator*(const Vectorf::Vector3f& v)
{
    const float _w = - (x * v.getX()) - (y * v.getY()) - (z * v.getZ());
    const float _x =   (w * v.getX()) + (y * v.getZ()) - (z * v.getX());
    const float _y =   (w * v.getY()) + (z * v.getX()) - (x * v.getY());
    const float _z =   (w * v.getZ()) + (x * v.getY()) - (y * v.getZ());

	Quaternion* ret = new Quaternion (_x, _y, _z, _w);

    return ret;
}
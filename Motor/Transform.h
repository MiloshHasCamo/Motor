#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Math.h"

using namespace Vectorf;
using namespace Matrixf;

class Transform
{
private:

	static float m_fov;
	static float m_width;
	static float m_height;
	static float m_zNear;
	static float m_zFar;

	Vector3f m_pos;
	Vector3f m_rot;
	Vector3f m_scale;

public:
	static void setProjection ( float fov, float width, float height, float zNear, float zFar );
	Transform ( Vector3f pos = Vector3f ( 0, 0, 0 ), Vector3f rot = Vector3f ( 0, 0, 0 ), Vector3f scale = Vector3f ( 1, 1, 1 ) );
	~Transform ( );

	Matrix4f getTransformation ( );
	Matrix4f getProjectedTransformation ( );

	Vector3f& getPosition ( );
	Vector3f& getRotation ( );
	Vector3f& getScale ( );

	void setPosition ( const Vector3f& scale );
	void setRotation ( const Vector3f& scale );
	void setScale ( const Vector3f& scale );
};

#endif//TRANSFORM_H_
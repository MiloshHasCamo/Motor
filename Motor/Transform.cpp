#include "Transform.h"

float Transform::m_zFar = 0;
float Transform::m_zNear = 0;
float Transform::m_fov = 0;
float Transform::m_width = 0;
float Transform::m_height = 0;

Transform::Transform(Vector3f pos, Vector3f rot, Vector3f scale)
{
	m_pos = pos;
	m_rot = rot;
	m_scale = scale;
}

Transform::~Transform()
{

}

Matrix4f Transform::getTransformation()
{
	Matrix4f translationMatrix;
	Matrix4f rotationMatrix;
	Matrix4f scaleMatrix;

	return translationMatrix * rotationMatrix * scaleMatrix;
}

Matrix4f Transform::getProjectedTransformation()
{
	Matrix4f transformationMatrix = getTransformation();
	Matrix4f projectionMatrix;
	Matrix4f cameraRotation;
	Matrix4f cameraTranslation;

	return projectionMatrix * cameraRotation * cameraTranslation * transformationMatrix;
}

Vector3f& Transform::getPosition()
{
	return m_pos;
}

Vector3f& Transform::getRotation()
{
	return m_rot;
}

Vector3f& Transform::getScale()
{
	return m_scale;
}

void Transform::setPosition(const Vector3f& pos)
{
	this->m_pos = pos;
}

void Transform::setRotation(const Vector3f& _rot)
{
	m_rot = _rot;
}

void Transform::setScale(const Vector3f& scale)
{
	this->m_scale = scale;
}

void Transform::setProjection(float fov, float width, float height, float zNear, float zFar)
{
	Transform::m_fov = fov;
	Transform::m_width = width;
	Transform::m_height = height;
	Transform::m_zNear = zNear;
	Transform::m_zFar = zFar;
}
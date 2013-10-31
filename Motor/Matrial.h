#ifndef MATRIAL_H_
#define MATRIAL_H_

#include "Texture.h"
#include "Vector.h"

using namespace Vectorf;

class Material
{
	Texture* texture;
	Vectorf::Vector3f color;
	float specularIntensity;
	float specularPower;

	Material ( Texture* texture = NULL, const Vector3f& color = Vector3f ( 1, 1, 1 ), float specularIntensity = 2, float specularPower = 32 )
	{
		this->texture = texture;
		this->color = color;
		this->specularIntensity = specularIntensity;
		this->specularPower = specularPower;
	}
};

#endif//MATRIAL_H_
#ifndef LIGHTMANAGER_H_
#define LIGHTMANAGER_H_

#include <SDL_opengl.h>
#include "Vector.h"

using namespace Vectorf;

#define LIGHT0 GL_LIGHT0
#define LIGHT1 GL_LIGHT1
#define LIGHT2 GL_LIGHT2
#define LIGHT3 GL_LIGHT3
#define LIGHT4 GL_LIGHT4
#define LIGHT5 GL_LIGHT5
#define LIGHT6 GL_LIGHT6
#define LIGHT7 GL_LIGHT7
			   
typedef GLuint LightSourceID;

struct LightSource 
{
	float* color;
	float* pos;
	float* diffuse;
	float* amb;
	float* spec;
	LightSourceID ID;

	LightSource ( );
	LightSource ( float* _pos, float* _diffuse, float* _amb,  float* _spec );
};

struct BaseLight
{
	Vector3f color;
	float intensity;
	GLuint ID;

	BaseLight(Vector3f color = Vector3f(0,0,0), float intensity = 0)
	{
		this->color = color;
		this->intensity = intensity;
	}
};

struct DirectionalLight
{
	BaseLight base;
	Vector3f direction;

	DirectionalLight(BaseLight base = BaseLight(), Vector3f direction = Vector3f(0,0,0))
	{
		this->base = base;
		this->direction = direction;
	}
};

struct Attenuation
{
	float constant;
	float linear;
	float exponent;

	Attenuation(float constant = 0, float linear = 0, float exponent = 1)
	{
		this->constant = constant;
		this->linear = linear;
		this->exponent = exponent;
	}
};

struct PointLight
{
	BaseLight base;
	Attenuation atten;
	Vector3f position;
	float range;

	PointLight(BaseLight base = BaseLight(), Attenuation atten = Attenuation(), Vector3f position = Vector3f(), float range = 0)
	{
		this->base = base;
		this->atten = atten;
		this->position = position;
		this->range = range;
	}
};

struct SpotLight
{
	PointLight pointLight;
	Vector3f direction;
	float cutoff;

	SpotLight(PointLight pointLight = PointLight(), Vector3f direction = Vector3f(), float cutoff = 0)
	{
		this->pointLight = pointLight;
		this->direction = direction;
		this->cutoff = cutoff;
	}
};

void EnableLighting ( unsigned int LightID );

void RenderLightSource ( LightSource light );

#endif//LIGHTMANAGER_H_
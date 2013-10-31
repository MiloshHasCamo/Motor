#ifndef FOGMANAGER_H_
#define FOGMANAGER_H_

#include <SDL_opengl.h>

struct Fog
{
	float startPoint;
	float endPoint;
	int mode;
	float* color;
};

void EnableFog ( Fog fog );

void RenderFog ( Fog fog );

#endif//FOGMANAGER_H_
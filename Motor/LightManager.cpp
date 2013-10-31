#include "LightManager.h"

void EnableLighting ( unsigned int LightID )
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(LightID);
	glEnable(GL_COLOR_MATERIAL);
}

LightSource::LightSource ( float* _pos, float* _diffuse, float* _amb,  float* _spec )
{
	pos = _pos;
	diffuse = _diffuse;
	amb = _amb;
	spec = _spec;

	glLightfv ( ID, GL_DIFFUSE, diffuse );
	glLightfv ( ID, GL_AMBIENT, amb );
	glLightfv ( ID, GL_POSITION, pos );
	glLightfv ( ID, GL_SPECULAR, spec );
}

LightSource::LightSource ( )
{
	glLightfv ( ID, GL_DIFFUSE, diffuse );
	glLightfv ( ID, GL_AMBIENT, amb );
	glLightfv ( ID, GL_POSITION, pos );
	glLightfv ( ID, GL_SPECULAR, spec );
}

void InitLightSource ( LightSource slight, LightSourceID lightsourceID )
{
	glLightfv ( lightsourceID, GL_DIFFUSE, slight.diffuse );
	glLightfv ( lightsourceID, GL_AMBIENT, slight.amb	  );
}

void RenderLightSource ( LightSource light )
{
	glLightfv(GL_LIGHT0, GL_POSITION, light.pos);
}
#ifndef PARTICLEMANAGER_H_
#define PARTICLEMANAGER_H_

#include <SDL_opengl.h>
#include <stdlib.h>

#define MAX_PARTICLES 5000

class Particle
{
public:
	float x, y, xVel, yVel, 
		width, height, *color;

	Particle ( float X, float Y, float w, float h );
	Particle ( float X, float Y, float w, float h, float* c );

	void  setXVEL ( float xvel );
	void  setYVEL ( float yvel );
	float getXVEL ( );
	void  Move    ( );
};

class ParticleManager
{
private:
	long l_particles;
	Particle** particles;

public:
	ParticleManager ( long particlecounter );
	ParticleManager ( float x, float y, long particlecounter, bool randomize );
	ParticleManager ( float x, float y, long particlecounter );
	ParticleManager ( float x, float y, float w, float h, long particlecounter );
	ParticleManager ( float x, float y, float w, float h, float* color, long particlecounter );

	virtual ~ParticleManager ( );
	
	float* getXVEL ( );
	void   Render  ( );
	void   Tick	   ( float* xVel, float* yVel );
};

#endif//PARTICLEMANAGER_H_
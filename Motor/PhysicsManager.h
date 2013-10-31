#ifndef PHYSICSENGINE_H_
#define PHYSICSENGINE_H_

#include "Entity.h"
#include "ParticleManager.h"
#include <SDL.h>

struct Collision
{
	bool CheckCollision2D	   ( float aX, float aY, float aW, float aH, float bX, float bY, float bW, float bH );
	bool CheckCollision2D	   ( Entity  a, Entity b );
	bool CheckCollision2D	   ( SDL_Rect a, SDL_Rect b );
	bool DetectBorderCollision ( int w, int h, SDL_Rect r );
};

class PhysicsEngine
{
private:
	float gravity;

public:
	Collision CollisionUtillities;

	PhysicsEngine ( float gravity );

	ParticleManager ExplosionPrep ( float x, float y, float power );
	void Explode2D ( ParticleManager manager );
	void Drop ( Entity );
	void Drop ( float yVel );
};

#endif//PHYSICSENGINE_H_
#include "PhysicsManager.h"

#pragma warning ( disable: 4244 ) 

ParticleManager PhysicsEngine::ExplosionPrep ( float x, float y, float power )
{
	return ParticleManager ( x, y, 50, true );
}

void PhysicsEngine::Explode2D ( ParticleManager manager )
{
	float* yVel = NULL;

	for ( int i = 0; i < 20; i++ )
	{
		Drop ( yVel [ i ] );
	}

	manager.Tick ( manager.getXVEL ( ), yVel );
}

bool Collision::CheckCollision2D ( float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh ) //Funcfion for checking collision
{
		 if ( Ay+Ah < By ) return false; 
	else if ( Ay > By+Bh ) return false; 
	else if ( Ax+Aw < Bx ) return false; 
	else if ( Ax > Bx+Bw ) return false; 
 
	return true; 
}

bool Collision::CheckCollision2D ( Entity a, Entity b )
{
		 if ( a.getVectors ( ) [ positions ]->getY ( ) + a.getVectors ( ) [ dimensions ]->getY ( ) < b.getVectors ( ) [ dimensions ]->getY ( ) ) return false; 
	else if ( a.getVectors ( ) [ positions ]->getY ( ) > b.getVectors ( ) [ positions  ]->getY ( ) + b.getVectors ( ) [ dimensions ]->getY ( ) ) return false;
	else if ( a.getVectors ( ) [ positions ]->getX ( ) + a.getVectors ( ) [ dimensions ]->getX ( ) < b.getVectors ( ) [ positions  ]->getX ( ) ) return false;
	else if ( a.getVectors ( ) [ positions ]->getX ( ) > b.getVectors ( ) [ positions  ]->getX ( ) + b.getVectors ( ) [ dimensions ]->getX ( ) ) return false;
 
	return true; 
}

void PhysicsEngine::Drop ( Entity en )
{
	en.setYVEL ( gravity );
}

bool Collision::DetectBorderCollision ( int w, int h, SDL_Rect r )
{
		 if ( r.x + r.w == w ) return true;
	else if ( r.x == 0 )	   return true;

		 if ( r.y + r.h == h ) return true;
	else if ( r.y == 0 )	   return true;

	return false;
}

void PhysicsEngine::Drop ( float yvel )
{
	yvel -= gravity;
}

PhysicsEngine::PhysicsEngine ( float g )
{
	gravity = g;
}
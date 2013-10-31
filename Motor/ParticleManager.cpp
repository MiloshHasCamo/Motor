#include "ParticleManager.h"

Particle::Particle ( float X, float Y, float w, float h )
{
	x = X;
	y = Y;
	width  = w;
	height = h;
}

Particle::Particle ( float X, float Y, float w, float h, float* c )
{
	x = X;
	y = Y;
	width  = w;
	height = h;

	for ( int i = 0; i < 3; i++ )
	{
		color[i] = c[i];
	}
}

void Particle::setXVEL ( float xvel )
{
	xVel = xvel;
}

void Particle::setYVEL ( float yvel )
{
	yVel = yvel;
}

void Particle::Move ()
{
	x += xVel;
	y += yVel;
}

ParticleManager::ParticleManager ( long particlecounter )
{
	for ( int i = 0; i < particlecounter; i++ )
	{
		particles [ i ] = new Particle ( 0, 0, 5, 5 );
	}

	l_particles = particlecounter;
}

ParticleManager::ParticleManager ( float x, float y, long particlecounter )
{
	for ( int i = 0; i < particlecounter; i++ )
	{
		particles [ i ] = new Particle ( x, y, 5, 5 );
	}

	l_particles = particlecounter;
}

ParticleManager::ParticleManager ( float x, float y, float w, float h, long particlecounter )
{
	for ( int i = 0; i < particlecounter; i++ )
	{
		particles [ i ] = new Particle ( x, y, w, h );
	}

	l_particles = particlecounter;
}

ParticleManager::ParticleManager ( float x, float y, float w, float h, float* color, long particlecounter )
{
	for ( int i = 0; i < particlecounter; i++ )
	{
		particles [ i ] = new Particle ( x, y, w, h, color );
	}

	l_particles = particlecounter;
}

void ParticleManager::Render ()
{
	for ( int i = 0; i < l_particles; i++ )
	{
		glColor3fv ( particles [ i ]->color );

		glBegin ( GL_QUADS );																					 
			glVertex2f ( particles[i]->x								, particles[i]->y						 );
			glVertex2f ( particles[i]->x + particles[l_particles]->width, particles[i]->y  						 );
			glVertex2f ( particles[i]->x + particles[l_particles]->width, particles[i]->y + particles[i]->height );
			glVertex2f ( particles[i]->x								, particles[i]->y + particles[i]->height );
		glEnd ();
	}
}

void ParticleManager::Tick ( float* xVel, float* yVel )
{
	for ( int i = 0; i < l_particles; i++ ) 
	{
		particles [ i ]->setXVEL ( xVel [ i ] );
		particles [ i ]->setYVEL ( yVel [ i ] );
	}
}

ParticleManager::~ParticleManager ( )
{
	for ( int i = 0; i < l_particles; i++ )
	{
		delete particles [ i ];
	}
}

ParticleManager::ParticleManager ( float x, float y, long lcounter, bool randomize )
{
	if ( randomize )
	{
		for ( int i = 0; i < lcounter; i++ )
		{
			particles [ i ] = new Particle ( x, y, 5, 5 );
		}

		l_particles = lcounter;
		
		int randy = rand ( ) % 1;
		
		for ( int i = 0; i < lcounter; i++ )
		{
			if  ( randy == 1 ) particles [ i ]->setXVEL (  10 );
			else               particles [ i ]->setXVEL ( -10 );
		
			particles [ i ]->setYVEL ( -5.5f );
		
			randy = rand ( ) % 1;
		}
	}else {
		for ( int i = 0; i < lcounter; i++ )
		{
			particles [ i ] = new Particle ( x, y, 5, 5 );
		}

		l_particles = lcounter;
	}
}

float* ParticleManager::getXVEL ( )
{
	float* XVEL = new float [ MAX_PARTICLES ];

	for ( int i = 0; i < l_particles; i++ )
	{
		XVEL [ i ] = particles [ i ]->getXVEL ( );
	}

	for ( int i = l_particles; i < MAX_PARTICLES; i++ )
	{
		XVEL [ i ] = NULL;
	}

	return XVEL;
}

float Particle::getXVEL ( )
{
	return xVel;
}
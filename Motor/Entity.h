#ifndef	Entity_H_
#define Entity_H_

#include <SDL.h>
#include <SDL_opengl.h>
#include "Vector.h"

#define velocities 2
#define positions  0
#define dimensions 1

class Entity
{
private:
	Vectorf::Vector3f* vel;
	Vectorf::Vector3f* pos;
	Vectorf::Vector3f* dim;
public:
	Entity ( );
	Entity ( Vectorf::Vector3f** );
	Entity ( Vectorf::Vector3f* position );
	Entity ( Vectorf::Vector3f* position, Vectorf::Vector3f* velocity );
	Entity ( Vectorf::Vector3f* position, Vectorf::Vector3f* velocity, Vectorf::Vector3f* dimension );
	Entity ( float, float );
	Entity ( float, float, float );
	Entity ( int, int );
	Entity ( float, float, int, int );
	Entity ( int, int, int, int, char* );

	virtual ~Entity ( );

	Entity operator =  ( Entity& );
	bool   operator == ( Entity& );
	bool   operator != ( Entity& );

	void Move    ( );
	void setXVEL ( float );
	void setYVEL ( float );

	Vectorf::Vector3f** getVectors ( );

	float getX	    ( );
	float getY      ( );
	int getWidth  ( );
	int getHeight ( );

	void Render ( );
};

#endif//Entity_H_
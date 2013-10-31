#include "Camera2D.h"

Camera2D::Camera2D ( )
{
	coord.x = 0;
	coord.y = 0;
	coord.z = 0;
}

Camera2D::Camera2D ( float x, float y, float z )
{
	coord.x = x;
	coord.y = y;
	coord.z = z;
}

Camera2D::Camera2D ( coordinate coordy )
{
	coord.x = coordy.x;
	coord.y = coordy.y;
	coord.z = coordy.z;
}

void Camera2D::Update ( )
{
	glMatrixMode( GL_MODELVIEW ); 
	glPopMatrix(); 
	glLoadIdentity(); 

	glTranslatef( -coord.x, -coord.y, 0.f );
	
	glPushMatrix();
}

void Camera2D::Control ( void ( f ( SDL_Event ) ), SDL_Event event )
{
	f ( event );
}
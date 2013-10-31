#include "Camera3D.h"

#pragma warning ( disable: 4244 )

Camera3D::Camera3D ( coordinate coordi )
{
	coord.x = coordi.x;
	coord.y = coordi.y;
	coord.z = coordi.z;
}

void Camera3D::Lock ( ) 
{
	if ( pitch > 90 )
	{
		pitch = 90;
	} else if ( pitch < -90 ) {
		pitch = -90;
	}

	if ( yaw < 0.0 )
	{
		yaw += 360;
	} else if ( yaw > 360 ){
		yaw -= 360;
	}
}

void Camera3D::Move ( float distance, float direction )
{
	float rad = ( yaw + direction ) * M_PI / 180;
	coord.x -= sin ( rad ) * distance;
	coord.y -= cos ( rad ) * distance;
}

void Camera3D::MoveUp ( float distance, float direction )
{
	float rad = ( pitch + direction ) * M_PI / 180;
	coord.y += sin ( rad ) * distance;
}

void Camera3D::Control ( float movevel, float mousevel, bool mi, SDL_Event event, void *(*f)(float, float, bool, SDL_Event) = NULL )
{
	if ( f == NULL ) control = overriden;

	if ( control != overriden ) 
	{
		if ( mi )
		{
			int MidX = 640/2;
			int MidY = 480/2;
			SDL_ShowCursor ( SDL_DISABLE );
			int tmpX, tmpY; 
			SDL_GetMouseState	   ( &tmpX, &tmpY );
			yaw += mousevel   * ( MidX-tmpX    );
			pitch += mousevel * ( MidY - tmpY  );
			Lock ( );
			SDL_WarpMouse ( MidX, MidY );

			Uint8* state = SDL_GetKeyState ( NULL );
			
			if ( state[SDLK_w] )
			{
				if ( pitch != 90 && pitch != -90 )
				{
					Move ( movevel, 0.0f );
				}
				MoveUp ( movevel, 0.0f );
			
			}else if ( state[SDLK_s] ) {
				if ( pitch != 90 && pitch != -90 )
				{
					Move ( movevel, 180.0f );
				}
				Move ( movevel, 180.0f );
			}

			if ( state[SDLK_a] )
			{
				Move ( movevel, 90.0  );
			} else if ( state [SDLK_d] ) {
				Move ( movevel, 270.0 );
			}
		}

		glRotatef ( -pitch, 1.0, 0.0, 0.0 );
		glRotatef ( -yaw,   0.0, 1.0, 0.0 );
	} else { 
		f ( movevel, mousevel, mi, event );
	}
}

void Camera3D::Update ( )
{
	glMatrixMode ( GL_MODELVIEW );
	glPopMatrix ( );
	glLoadIdentity ( );

	glTranslatef ( -coord.x, -coord.y, -coord.z );

	glPushMatrix ( );
}
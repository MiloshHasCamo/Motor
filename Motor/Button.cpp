#include "Button.h"

Texture Button::getSheet  ( )
{
	return sheet;
}

void Button::Listen (  void (f (void)), SDL_Event event )
{
	if ( event.type == SDL_MOUSEBUTTONDOWN )
	{
		if ( event.button.button == SDL_BUTTON_LEFT )
		{
			if( ( event.button.x > frame.x ) && ( event.button.x < frame.x + frame.w ) 
				&&
				( event.button.y > frame.y ) && (event.button.y < frame.y + frame.h ) )
			{
				RenderRollOverSheet ( );
			}
		}
	}

	if ( event.type == SDL_MOUSEBUTTONUP )
	{
		if ( event.button.button == SDL_BUTTON_LEFT )
		{
			if( ( event.button.x > frame.x ) && ( event.button.x < frame.x + frame.w ) 
				&&
				( event.button.y > frame.y ) && (event.button.y < frame.y + frame.h ) )
			{
				f ( );
			}
		}
	}
}

Button::Button ( Texture cT )
{
	sheet = cT;
}

void Button::LoadSheet ( char* pTex )
{
	sheet.LoadTexture ( pTex );
}

void Button::LoadRollOver ( char* pFile )
{
	RollOver.LoadTexture ( pFile );
}

Button::Button ( int x, int y )
{
	frame.x = x;
	frame.y = y;
}

Button::Button ( SDL_Rect rct )
{
	frame.x = rct.x;
	frame.h = rct.h;
	frame.w = rct.w;
	frame.y = rct.y;
}

Button::Button ( int width, int height, void* pVoid )
{
	frame.w = width;
	frame.h = height;
}

Button::Button ( int x, int y, int width, int height )
{
	frame.x = x;
	frame.y = y;
	frame.w = width;
	frame.h = height;
}

SDL_Rect Button::getRect   ( )
{
	return frame;
}

int	Button::getX	   ( )
{
	return frame.x;
}

int	Button::getY      ( )
{
	return frame.y;
}

int	Button::getWidth  ( )
{
	return frame.w;
}

int	Button::getHeight ( )
{
	return frame.h;
}

void Button::Render ( )
{
	#pragma warning ( disable: 4244 )

	sheet.Bind ( );

	glBegin ( GL_QUADS );
		glTexCoord2f ( 0, 0 ); glVertex2f ( frame.x			 , frame.y );
		glTexCoord2f ( 1, 0 ); glVertex2f ( frame.x + frame.w, frame.y );
		glTexCoord2f ( 1, 1 ); glVertex2f ( frame.x + frame.w, frame.y + frame.h );
		glTexCoord2f ( 0, 1 ); glVertex2f ( frame.x			 , frame.y + frame.h );
	glEnd ( );
}

void Button::RenderRollOverSheet ( )
{
	#pragma warning ( disable: 4244 )

	RollOver.Bind ( );

	glBegin ( GL_QUADS );
		glTexCoord2f ( 0, 0 ); glVertex2f ( frame.x			 , frame.y );
		glTexCoord2f ( 1, 0 ); glVertex2f ( frame.x + frame.w, frame.y );
		glTexCoord2f ( 1, 1 ); glVertex2f ( frame.x + frame.w, frame.y + frame.h );
		glTexCoord2f ( 0, 1 ); glVertex2f ( frame.x			 , frame.y + frame.h );
	glEnd ( );
}
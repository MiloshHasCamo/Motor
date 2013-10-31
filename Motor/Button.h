#ifndef BUTTON_H_
#define BUTTON_H_

#include <SDL.h>
#include "Entity.h"
#include "Texture.h"

class Button
{
private:
	SDL_Rect frame;
	Texture sheet;
	Texture RollOver;

	void RenderRollOverSheet ( );

public:
	Button ( SDL_Rect );
	Button ( int, int );
	Button ( int, int, void* );
	Button ( int, int, int, int );
	Button ( Texture cT );

	SDL_Rect getRect   ( );
	int		 getX	   ( );
	int		 getY      ( );
	int		 getWidth  ( );
	int		 getHeight ( );
	Texture getSheet  ( );

	void LoadSheet ( char* );
	void LoadRollOver ( char* );
	void Render ( );
	void Listen ( void (f (void)), SDL_Event);
};
#endif//BUTTON_H_
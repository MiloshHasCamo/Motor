#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Entity.h"

class Texture
{
private:
	GLuint texture;
	GLenum texture_format;
	GLint nOfColors;
	SDL_Surface* surface;

public:
	void		 Unbind ( );
	void		 LoadTexture ( const char* pFile );
	GLuint		 getID		 ( void );
	void		 Bind ( );
	int			 BlendRGB ( int, int, int );
	void         Render ( Entity );
};

#endif//TEXTURE_H_
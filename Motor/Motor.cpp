#include "Motor.h"
#include <gl\glut.h>

void ResetColor ( )
{
	glColor3f ( 1.0f, 1.0f, 1.0f );
}

SDL_Surface* LoadImageFile ( const char* file )
{
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load ( file );

	if ( loadedImage != NULL )
	{
		optimizedImage = SDL_DisplayFormat ( loadedImage );
		SDL_FreeSurface ( loadedImage );
	}

	return optimizedImage;
}

void RenderSurface ( int x, int y, SDL_Surface* src, SDL_Surface* dst )
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface ( src, NULL, dst, &offset );
}

Window* Init ( int width, int height, char* ptitle, bool fullscreen ) 
{
	SDL_Surface* pMainSurface = NULL;
	Window* win = ( Window* ) malloc ( sizeof ( Window ) );

	if  ( fullscreen ) pMainSurface = SDL_SetVideoMode ( width, height, 32, SDL_OPENGL | SDL_FULLSCREEN ); 
	else			   pMainSurface = SDL_SetVideoMode ( width, height, 32, SDL_OPENGL );

	SDL_WM_SetCaption ( ptitle, NULL );

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); 

	glEnable( GL_TEXTURE_2D );
 
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
 
	glViewport( 0, 0, width, height );
 
	glClear( GL_COLOR_BUFFER_BIT );
 
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
 
	glOrtho ( 0.0f, width, height, 0.0f, -1.0f, 1000.0f ); 
 
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glBlendFunc ( GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA );
	glEnable ( GL_BLEND );

	glewInit ( );
	
	win->m_pMain  = pMainSurface;
	win->m_width  = width;
	win->m_height = height;

	return win;
}

void RenderCube ( float size )
{
    float difamb[] = { 1.0f, 0.5f, 0.3f, 1.0f };
    glBegin(GL_QUADS);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, difamb);

            glNormal3f(0.0,0.0,1.0);
            glVertex3f(size/2,size/2,size/2);
            glVertex3f(-size/2,size/2,size/2);
            glVertex3f(-size/2,-size/2,size/2);
            glVertex3f(size/2,-size/2,size/2);

            glNormal3f(-1.0,0.0,0.0);
            glVertex3f(-size/2,size/2,size/2);
            glVertex3f(-size/2,-size/2,size/2);
            glVertex3f(-size/2,-size/2,-size/2);
            glVertex3f(-size/2,size/2,-size/2);

            glNormal3f(0.0,0.0,-1.0); 
            glVertex3f(size/2,size/2,-size/2);
            glVertex3f(-size/2,size/2,-size/2);
            glVertex3f(-size/2,-size/2,-size/2);
            glVertex3f(size/2,-size/2,-size/2);

            glNormal3f(1.0,0.0,0.0);
            glVertex3f(size/2,size/2,size/2);
            glVertex3f(size/2,-size/2,size/2);
            glVertex3f(size/2,-size/2,-size/2);
            glVertex3f(size/2,size/2,-size/2);

            glNormal3f(0.0,1.0,0.0);
            glVertex3f(size/2,size/2,size/2);
            glVertex3f(-size/2,size/2,size/2);
            glVertex3f(-size/2,size/2,-size/2);
            glVertex3f(size/2,size/2,-size/2);

            glNormal3f(0.0,-1.0,0.0);
            glVertex3f(size/2,-size/2,size/2);
            glVertex3f(-size/2,-size/2,size/2);
            glVertex3f(-size/2,-size/2,-size/2);
            glVertex3f(size/2,-size/2,-size/2);
    glEnd();
}

void mtSwapBuffers ( void )
{
	SDL_GL_SwapBuffers ( );
}
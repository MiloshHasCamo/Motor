#include "Skybox.h"

Skybox::Skybox ( std::string folder )
{
	folder += "/";
	std::string tmp;
	tmp = folder;
	
	tmp += "left.bmp";

	texture [ SKYLEFT   ].LoadTexture ( tmp.c_str() );

	tmp = folder;
	tmp += "right.bmp";

	texture [ SKYRIGHT  ].LoadTexture ( tmp.c_str() );

	tmp = folder;
	tmp += "back.bmp";

	texture [ SKYBACK   ].LoadTexture ( tmp.c_str() );

	tmp = folder;
	tmp += "front.bmp";

	texture [ SKYFRONT  ].LoadTexture ( tmp.c_str() );

	tmp = folder;
	tmp += "top.bmp";

	texture [ SKYTOP    ].LoadTexture ( tmp.c_str() );

	tmp = folder;
	tmp += "bottom.bmp";

	texture [ SKYBOTTOM ].LoadTexture ( tmp.c_str() );

	textureID [ SKYLEFT   ] = texture [ SKYLEFT   ].getID ( );
	textureID [ SKYRIGHT  ] = texture [ SKYRIGHT  ].getID ( );
	textureID [ SKYBACK   ] = texture [ SKYBACK   ].getID ( );
	textureID [ SKYFRONT  ] = texture [ SKYFRONT  ].getID ( );
	textureID [ SKYTOP    ] = texture [ SKYTOP    ].getID ( );
	textureID [ SKYBOTTOM ] = texture [ SKYBOTTOM ].getID ( );
}

Skybox::~Skybox ( void )
{ 
	glDeleteTextures ( 6, &textureID[0] );
}

void Skybox::Render ( float size )
{
	GLboolean b1 = glIsEnabled ( GL_TEXTURE_2D );
	
	glDisable ( GL_LIGHTING   );	
	glDisable ( GL_DEPTH_TEST );
	glEnable  ( GL_TEXTURE_2D );
	
	glBindTexture ( GL_TEXTURE_2D, textureID [ SKYBACK ] );
	
	glBegin ( GL_QUADS );	
		glTexCoord2f ( 0, 0 ); glVertex3f (  size/2,  size/2, size/2 );
		glTexCoord2f ( 1, 0 ); glVertex3f ( -size/2,  size/2, size/2 );
		glTexCoord2f ( 1, 1 ); glVertex3f ( -size/2, -size/2, size/2 );
		glTexCoord2f ( 0, 1 ); glVertex3f (  size/2, -size/2, size/2 );
	glEnd();

	glBindTexture ( GL_TEXTURE_2D, textureID [ SKYLEFT ] );
	
	glBegin(GL_QUADS);	
		glTexCoord2f ( 0, 0 ); glVertex3f ( -size/2,  size/2,  size/2 );
		glTexCoord2f ( 1, 0 ); glVertex3f ( -size/2,  size/2, -size/2 );
		glTexCoord2f ( 1, 1 ); glVertex3f ( -size/2, -size/2, -size/2 );
		glTexCoord2f ( 0, 1 ); glVertex3f ( -size/2, -size/2,  size/2 );
	glEnd();

	glBindTexture ( GL_TEXTURE_2D, textureID [ SKYFRONT ] );
	
	glBegin ( GL_QUADS );	
		glTexCoord2f ( 1, 0 ); glVertex3f(  size/2,  size/2, -size/2 );
		glTexCoord2f ( 0, 0 ); glVertex3f( -size/2,  size/2, -size/2 );
		glTexCoord2f ( 0, 1 ); glVertex3f( -size/2, -size/2, -size/2 );
		glTexCoord2f ( 1, 1 ); glVertex3f(  size/2, -size/2, -size/2 );
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textureID [ SKYRIGHT ] );	
	
	glBegin ( GL_QUADS );
		glTexCoord2f ( 0, 0 ); glVertex3f ( size/2,  size/2, -size/2 );
		glTexCoord2f ( 1, 0 ); glVertex3f ( size/2,  size/2,  size/2 );
		glTexCoord2f ( 1, 1 ); glVertex3f ( size/2, -size/2,  size/2 );
		glTexCoord2f ( 0, 1 ); glVertex3f ( size/2, -size/2, -size/2 );
	glEnd();

	glBindTexture ( GL_TEXTURE_2D, textureID [ SKYTOP ] );	

	glBegin ( GL_QUADS );			//top face
		glTexCoord2f ( 1, 0 ); glVertex3f (  size/2, size/2,  size/2 );
		glTexCoord2f ( 0, 0 ); glVertex3f ( -size/2, size/2,  size/2 );
		glTexCoord2f ( 0, 1 ); glVertex3f ( -size/2, size/2, -size/2 );
		glTexCoord2f ( 1, 1 ); glVertex3f (  size/2, size/2, -size/2 );
	glEnd();

	glBindTexture ( GL_TEXTURE_2D, textureID [ SKYBOTTOM ] );

	glBegin ( GL_QUADS );
		glTexCoord2f ( 1, 1 ); glVertex3f (  size/2, -size/2,  size/2 );
		glTexCoord2f ( 0, 1 ); glVertex3f ( -size/2, -size/2,  size/2 );
		glTexCoord2f ( 0, 0 ); glVertex3f ( -size/2, -size/2, -size/2 );
		glTexCoord2f ( 1, 0 ); glVertex3f (  size/2, -size/2, -size/2 );
	glEnd();

	glEnable ( GL_LIGHTING );
	
	glEnable ( GL_DEPTH_TEST );
	
	if ( !b1 )
		glDisable ( GL_TEXTURE_2D );
}
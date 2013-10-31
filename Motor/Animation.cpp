//include animation.h
#include "Animation.h"

///////////////////ANIMATION BASE IMPLEMENTATION////////////////
/////////          implements base                    //////////
/////////          class functions and                //////////
/////////          and operators                      //////////
////////////////////////////////////////////////////////////////

Animation::Animation::Animation ( )
{
	index = 0;
	log = new Log ( "AnimationLog" );
}

Animation::Animation::~Animation ( )
{
	log->~Log ( );
	delete log;
}

void Animation::Animation::operator++ ( )
{
	index++;
}

///////////////////ANIMATION 2D IMPLEMENTATION////////////////
/////////          implements 2D                    //////////
/////////          functions and                    //////////
/////////          and operators                    //////////
//////////////////////////////////////////////////////////////

Animation::Animation2D::Animation2D ( std::string files [ ], float x, float y, int width, int height ): Animation ( )
{
	frameCounter = sizeof ( files ) / 4;
	for ( int i = 0; i < frameCounter; i++ )
	{
		frames [ i ] = new Texture ( );
	}
	FramesEntity = new Entity ( x, y, ( int )width, ( int )height );
}

Animation::Animation2D::Animation2D ( std::string files [ ], Vectorf::Vector2f pos, Vectorf::Vector2f dim ): Animation ( )
{
	frameCounter = sizeof ( files ) / 4;
	for ( int i = 0; i < frameCounter; i++ )
	{
		frames [ i ] = new Texture ( );
	}
	FramesEntity = new Entity ( pos.getX ( ), pos.getY ( ), ( int )dim.getX ( ), ( int )dim.getY ( ) );
}

Animation::Animation2D::~Animation2D ( )
{	
	delete FramesEntity;
	delete log;
	delete [ ] frames;
}

void Animation::Animation2D::Render ( )
{
	Entity& en = *FramesEntity;
	frames [ index ]->Render ( en );
}

///////////////////ANIMATION 3D IMPLEMENTATION////////////////
/////////          implements 3D                    //////////
/////////          functions and                    //////////
/////////          and operators                    //////////
//////////////////////////////////////////////////////////////

Animation::Animation3D::Animation3D ( string files [ ], Vectorf::Vector3f* posi, Vectorf::Vector3f* dime ): Animation ( )
{
	loader = new objloader ( );
	frameCounter = sizeof ( files ) / 4;
	for ( int i = 0; i < frameCounter; i++ )
	{
		DisplayIDs [ i ] = loader->load ( files [ i ].c_str ( ) );
	}
	pos = new Vectorf::Vector3f ( posi->getX ( ), posi->getY ( ), posi->getZ ( ) );
	dim = new Vectorf::Vector3f ( posi->getX ( ), posi->getY ( ), posi->getZ ( ) );				 
}

Animation::Animation3D::Animation3D ( string files [ ], float X, float Y, float Z, float w, float h, float d ): Animation ( )
{
	loader = new objloader ( );
	frameCounter = sizeof ( files ) / 4;
	for ( int i = 0; i < frameCounter; i++ )
	{
		DisplayIDs [ i ] = loader->load ( files [ i ].c_str ( ) );
	}
	pos->setX ( X ); dim->setX ( w ); 
	pos->setY ( Y ); dim->setY ( h );
	pos->setZ ( Z ); dim->setZ ( d );
}

Animation::Animation3D::~Animation3D ( )
{
	loader->~objloader ( );
	log->~Log ( );

	delete loader;
	delete log;
	delete pos;
	delete dim;
	for ( int i = 0; i < frameCounter; i++ )
	{
		glDeleteLists ( DisplayIDs [ i ], 1 );
	}
}

void Animation::Animation3D::Render (  )
{
	glCallList ( DisplayIDs [ index ] );
}
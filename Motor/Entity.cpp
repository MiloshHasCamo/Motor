#include "Entity.h"

Entity::~Entity ( )
{
	delete pos;
	delete dim;
	delete vel;
}

Entity::Entity ( )
{
	pos->setX ( 0 );
	pos->setY ( 0 );
	pos->setZ ( 0 );

	dim->setX ( 1 );
	dim->setY ( 1 );
	dim->setZ ( 1 );

	vel->setX ( 0 );
	vel->setY ( 0 );
	vel->setZ ( 0 );
}

void Entity::Render ( )
{
	glBegin ( GL_QUADS );
		glTexCoord2i( 0, 0 ); glVertex2f ( pos->getX ( )				, pos->getY ( )		    );
		glTexCoord2i( 1, 0 ); glVertex2f ( pos->getX ( ) + dim->getX ( ), pos->getY ( )		    );
		glTexCoord2i( 1, 1 ); glVertex2f ( pos->getX ( ) + dim->getX ( ), pos->getY ( ) + dim->getY ( ) );
		glTexCoord2i( 0, 1 ); glVertex2f ( pos->getX ( )				, pos->getY ( ) + dim->getY ( ) );
	glEnd ();
}

Entity Entity::operator= ( Entity& other )
{
	return Entity ( other.getX ( ), other.getY ( ), other.getWidth ( ), other.getHeight ( ) );
}

bool Entity::operator== ( Entity& other )
{
	if ( other.getVectors ( ) [ positions ]->getX ( ) != pos->getX ( ) )
		return false;			 
	if ( other.getVectors ( ) [ positions ]->getY ( ) != pos->getY ( ) )
		return false;			 
	if ( other.getVectors ( ) [ velocities ]->getX ( ) != dim->getX ( ) )
		return false;			 
	if ( other.getVectors ( ) [ velocities ]->getY ( ) != dim->getY ( ) )
		return false;

	return true;
}

bool Entity::operator!= ( Entity& other )
{
	if ( other.getVectors ( ) [ positions ]->getX ( ) != pos->getX ( ) )
		return true;			 
	if ( other.getVectors ( ) [ positions ]->getY ( ) != pos->getY ( ) )
		return true;			 
	if ( other.getVectors ( ) [ velocities ]->getX ( ) != dim->getX ( ) )
		return true;			 
	if ( other.getVectors ( ) [ velocities ]->getY ( ) != dim->getY ( ) )
		return true;

	return false;
}

Entity::Entity ( Vectorf::Vector3f** rct )
{
	pos->setX ( rct [ positions ]->getX ( ) );
	pos->setY ( rct [ positions ]->getY ( ) );
	pos->setZ ( rct [ positions ]->getZ ( ) );

	dim->setX ( rct [ dimensions ]->getX ( ) );
	dim->setY ( rct [ dimensions ]->getY ( ) );
	dim->setZ ( rct [ dimensions ]->getZ ( ) );

	vel->setX ( rct [ velocities ]->getX ( ) );
	vel->setY ( rct [ velocities ]->getY ( ) );
	vel->setZ ( rct [ velocities ]->getZ ( ) );
}

Entity::Entity ( float x, float y )
{
	pos->setX ( x );
	pos->setY ( y );
	pos->setZ ( 0 );

	dim->setX ( 0 );
	dim->setY ( 0 );
	dim->setZ ( 1 );

	vel->setX ( 0 );
	vel->setY ( 0 );
	vel->setZ ( 0 );
}

Entity::Entity ( int width, int height )
{
	pos->setX ( 0 );
	pos->setY ( 0 );
	pos->setZ ( 0 );

	dim->setX ( ( float ) width );
	dim->setY ( ( float ) height );
	dim->setZ ( 1 );

	vel->setX ( 0 );
	vel->setY ( 0 );
	vel->setZ ( 0 );
}

Entity::Entity ( float x, float y, int width, int height )
{
	pos = new Vectorf::Vector3f ( x, y, 0 );
	dim = new Vectorf::Vector3f ( ( float ) width, ( float ) height, 0 );
	vel = new Vectorf::Vector3f ( 0, 0, 0 );
}

Vectorf::Vector3f** Entity::getVectors ( )
{
#pragma warning ( disable: 4172 )

	Vectorf::Vector3f* vecs [ 3 ];
	
	for ( int i = 0; i < 3; i++ ) vecs [ i ] = new Vectorf::Vector3f ( );

	vecs [ 1 ] = pos;
	vecs [ 1 ] = dim;
	vecs [ 1 ] = vel;
	
	return vecs;
#pragma warning ( default: 4172 )
}

float Entity::getX ( )
{
	return pos->getX ( );
}

float Entity::getY ( )
{
	return pos->getY ( );
}

int Entity::getWidth ( )
{
	return ( int ) dim->getX ( );
}

int Entity::getHeight ( )
{
	return ( int ) dim->getY ( );
}

void Entity::setXVEL ( float x )
{
	vel->setX ( x );
}

void Entity::setYVEL ( float y )
{
	vel->setX ( y );
}

void Entity::Move ( )
{
	pos->setX ( pos->getX ( ) + vel->getX ( ) );
	pos->setY ( pos->getY ( ) + vel->getY ( ) );
	pos->setZ ( pos->getZ ( ) + vel->getZ ( ) );
}

Entity::Entity ( Vectorf::Vector3f* posy )
{
	pos->setX ( posy->getX ( ) );
	pos->setX ( posy->getY ( ) );
	pos->setX ( posy->getZ ( ) );
}

Entity::Entity ( Vectorf::Vector3f* posy, Vectorf::Vector3f* veli )
{
	pos->setX ( posy->getX ( ) ); vel->setX ( veli->getX ( ) );
	pos->setX ( posy->getY ( ) ); vel->setX ( veli->getY ( ) );
	pos->setX ( posy->getZ ( ) ); vel->setX ( veli->getZ ( ) );
}

Entity::Entity ( Vectorf::Vector3f* posy, Vectorf::Vector3f* veli, Vectorf::Vector3f* dimi )
{
	pos->setX ( posy->getX ( ) ); vel->setX ( veli->getX ( ) ); dim->setX ( dimi->getX ( ) );
	pos->setX ( posy->getY ( ) ); vel->setX ( veli->getY ( ) );	dim->setX ( dimi->getY ( ) );
	pos->setX ( posy->getZ ( ) ); vel->setX ( veli->getZ ( ) );	dim->setX ( dimi->getZ ( ) );
}

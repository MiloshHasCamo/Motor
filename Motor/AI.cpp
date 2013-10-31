#include "AI.h"

static bool TargetIsTooTheLeft ( Entity me, Entity target )
{														
	if ( me.getX ( ) > target.getX ( ) )
		return true;
	return false;
}														

static bool TargetIsTooTheRight ( Entity me, Entity target )
{
	if ( me.getX ( ) > target.getX ( ) )
		return false;
	return true;
}

static bool TargetIsAbove ( Entity me, Entity target )
{
	if ( me.getY ( ) > target.getY ( ) )
		return false;
	return true;
}

static bool TargetIsBelow ( Entity me, Entity target )
{
	if ( me.getY ( ) > target.getY ( ) )
		return true;
	return false;
}

Path Locate2DPath ( Entity seeker, Entity dst )
{
	Path path;
	Entity SeekTemp = Entity ( seeker.getVectors ( ) );

	path [ 0 ] = Entity ( SeekTemp.getX ( ), SeekTemp.getY ( ) );
	
	int i = 0;

	while ( SeekTemp != dst )
	{
		///////////////////////// X-AXIS //////////////////////////

		if ( TargetIsTooTheLeft ( SeekTemp, dst ) )
		{
			//Add To Path.
			path [ i ] = Entity ( SeekTemp.getX ( ) - SeekTemp.getWidth ( ), SeekTemp.getY ( ) );
			
			//Move Temp.
			SeekTemp.setXVEL ( SeekTemp.getX ( ) - SeekTemp.getWidth ( ) );
			SeekTemp.Move ( );
		
		} else if ( TargetIsTooTheRight ( SeekTemp, dst ) ) {
			
			//Add To Path.
			path [ i ] = Entity ( SeekTemp.getX ( ) + SeekTemp.getWidth ( ), SeekTemp.getY ( ) );

			//Move Temp.
			SeekTemp.setXVEL ( SeekTemp.getX ( ) + SeekTemp.getWidth ( ) );
			SeekTemp.Move ( );
		}

		///////////////////////// Y-AXIS //////////////////////////
		
		if ( TargetIsAbove ( SeekTemp, dst ) )
		{
			//Add To Path.
			path [ i ] = Entity ( SeekTemp.getX ( ), SeekTemp.getY ( ) - dst.getHeight ( ) );
			
			//Move Temp.
			SeekTemp.setYVEL ( SeekTemp.getY ( ) - dst.getHeight ( ) );
			SeekTemp.Move ( );
		
		} else if ( TargetIsBelow ( SeekTemp, dst ) ) {
			
			//Add To Path.
			path [ i ] = Entity ( SeekTemp.getX ( ), SeekTemp.getY ( ) + dst.getHeight ( ) );

			//Move Temp.
			SeekTemp.setYVEL ( SeekTemp.getY ( ) + dst.getHeight ( ) );
			SeekTemp.Move ( );
		}

		i++;
	}
	return path;
}
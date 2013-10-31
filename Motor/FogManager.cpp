#include "FogManager.h"

void EnableFog ( Fog fog )
{
	glEnable ( GL_FOG );
	glFogi   ( GL_FOG_MODE, fog.mode );
	glFogf   ( GL_FOG_START, fog.startPoint );
	glFogf	 ( GL_FOG_END, fog.endPoint );
}

void RenderFog ( Fog fog )
{
	glFogfv ( GL_FOG_COLOR, fog.color );
}
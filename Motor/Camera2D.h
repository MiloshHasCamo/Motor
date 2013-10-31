#ifndef CAMERA2D_H_
#define CAMERA2D_H_

#include "OpenGLUtils.h"

class Camera2D
{
private:
	coordinate coord;
public:
	Camera2D ( );
	Camera2D ( float x, float y, float z );
	Camera2D ( coordinate coord );

	void Update ( );
	void Control ( void ( f ( SDL_Event ) ), SDL_Event event );
};

#endif//CAMERA2D_H_
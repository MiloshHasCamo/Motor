#ifndef CAMERA3D_H_
#define CAMERA3D_H_

#include "OpenGLUtils.h"

#define overriden false
#define free	  true

class Camera3D
{
private:
	coordinate coord;
	float pitch, yaw;
	bool control;
	
public:
	Camera3D ( coordinate coord );
	Camera3D ( float, float, float );
	
	void Lock ( );
	void Move ( float, float );
	void MoveUp  ( float, float );
	void Control ( float, float, bool, SDL_Event, void *(*f)(float, float, bool, SDL_Event) );
	void Update  ( );
};

#endif//CAMERA3D_H_
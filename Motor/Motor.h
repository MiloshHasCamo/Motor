#ifndef SDLUTILS_H_
#define SDLUTILS_H_

#define GLEW_STATIC
#define NO_SDL_GLEXT

#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Audio.h"
#include "Button.h"
#include "Camera2D.h"
#include "Camera3D.h"
#include "Entity.h"
#include "FogManager.h"
#include "LightManager.h"
#include "NetworkManager.h"
#include "OpenGLUtils.h"
#include "ParticleManager.h"
#include "PhysicsManager.h"
#include "Skybox.h"
#include "Texture.h"
#include "FileUtillities.h"
#include "Math.h"
#include "Window.h"
#include "Input.h"
#include "Window.h"
#include "Shader.h"
#include "Transform.h"
#include "Matrial.h"

using namespace std;

Window* Init		       ( int, int, char*, bool );

void ResetColor			   ( );

SDL_Surface* LoadImageFile ( const char* ); 

void RenderSurface		   ( int, int, SDL_Surface*, SDL_Surface* );

void RenderTexture		   ( Entity, Texture );

void RenderCube			   ( float size );

void MotorLispMain         ( char* file );

void mtSwapBuffers		   ( void );

#endif//SDLUTILS_H_
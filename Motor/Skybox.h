#ifndef SKYBOX_H_
#define SKYBOX_H_

#include "Texture.h"
#include <string>

enum { SKYLEFT = 0, SKYBACK, SKYRIGHT, SKYFRONT, SKYTOP, SKYBOTTOM };

class Skybox
{
private:
	Texture texture [ 6 ];
	unsigned int textureID [ 6 ]; 
public:
	 Skybox ( std::string folder );
	~Skybox ( );
	
	void Render ( float size );
};

#endif//SKYBOX_H_
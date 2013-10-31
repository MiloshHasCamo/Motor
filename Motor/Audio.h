#ifndef AUDIO_H_
#define AUDIO_H_

#include <iostream>
#include <fstream>
#include <cstring>
#include <AL/al.h>
#include <AL/alc.h>
#include "Math.h"

#define NUM_SOUNDS 50

using namespace Vectorf;

int CreateOpenALContext ( );

void DestroyOpenALContext ( );

class Sound
{
private:
	bool loaded;
	Vector3f position;
	string file;
	int& chan; 
	int& samplerate;
	int& bps;
	int& size;
	char* data;

	ALuint sourceID;
	ALuint bufferID, format;

	bool isBigEndian ( );
	int convertToInt ( char* buffer, int len );

public:
	 Sound ( int _chan, int _samplerate, int _bps, int _size, float posX, float posY, float posZ );
	~Sound ( );
	char* LoadWav ( const char* filename );
	void Play ( );
	void setPosition ( float, float, float );
	void UpdatePosition ( );
};

#endif//AUDIO_H_
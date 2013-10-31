#ifndef FILE_UTILLITIES_H_
#define FILE_UTILLITIES_H_

#include <iostream>
#include <fstream>
#include <string>
#include "OpenGLUtils.h"
#include <SDL_image.h>

using namespace std;

class Log
{
private:
	const char* filename;
	FILE* fileOBJ;

public:
	Log  ( );
	Log  ( char* filename );
	~Log ( );
	
	FILE* getFILE ( );
	const char* getFileName ( );

	const char* Read ( );
	void Writeln ( char* msg );
	void Write ( char* msg );
};

typedef struct {
	unsigned char imageTypeCode;
	short int imageWidth;
	short int imageHeight;
	unsigned char bitCount;
	unsigned char* imageData;
} TGA ;

static GLuint LoadTGATexture ( char* pfile, TGA* tga );

static GLuint LoadRegImage ( char* pfile );

GLuint LoadTexture ( char* file );

bool LoadFileContents ( const char* file, string& str );

bool Contains ( char* str, char* substr ); 

#endif//FILE_UTILLITIES_H_
#include "FileUtillities.h"

bool Contains ( char* str, char* substr )
{
	string* temp = new string ( str );

	if ( temp->find ( substr ) != string::npos )
		return true;
	return false;
}

bool LoadFileContents ( const char* file, string& str )
{
	ifstream in ( file );

	if ( !in.is_open ( ) )
	{	cerr << "Unable to Open File " << file << " For Loading contents" << endl;
		return false;
	}

	char tmp [ 300 ];

	while ( !in.eof ( ) ) 
	{
		in.getline ( tmp, 300 );
		str += tmp;
		str += '\n';
	}
	return true;
}

static GLuint LoadRegImage ( char* pfile )
{
	GLuint texture;			// This is a handle to our texture object
	SDL_Surface *surface;	// This surface will tell us the details of the image
	GLenum texture_format;
	GLint  nOfColors;
	Log log;

	if ( (surface = IMG_Load(pfile)) ) { 
	 
		// Check that the image's width is a power of 2
		if ( (surface->w & (surface->w - 1)) != 0 ) {
			log.Write("warning: image.bmp's width is not a power of 2\n");
		}
	 
		// Also check if the height is a power of 2
		if ( (surface->h & (surface->h - 1)) != 0 ) {
			log.Write("warning: image.bmp's height is not a power of 2\n");
		}
	 
	        // get the number of channels in the SDL surface
	        nOfColors = surface->format->BytesPerPixel;
	        if (nOfColors == 4)     // contains an alpha channel
	        {
	                if (surface->format->Rmask == 0x000000ff)
	                        texture_format = GL_RGBA;
	                else
	                        texture_format = GL_BGRA;
	        } else if (nOfColors == 3)     // no alpha channel
	        {
	                if (surface->format->Rmask == 0x000000ff)
	                        texture_format = GL_RGB;
	                else
	                        texture_format = GL_BGR;
	        } else {
	                log.Write("warning: the image is not truecolor..  this will probably break\n");
	                // this error should not go unhandled
	        }
	 
		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &texture );
	 
		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, texture );
	 
		// Set the texture's stretching properties
	        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	 
		// Edit the texture object's image data using the information SDL_Surface gives us
		glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
	                      texture_format, GL_UNSIGNED_BYTE, surface->pixels );
	    } 
	    else {
	    	log.Write ( "SDL could not load image.bmp: %s\n" );
	    	return NULL;
	    }
		return texture;
}

static GLuint LoadTGATexture ( char* filename, TGA* tgaFile )
{
	FILE *filePtr;
    unsigned char ucharBad;
    short int sintBad;
    long imageSize;
    int colorMode;
    unsigned char colorSwap;

    // Open the TGA file.
    filePtr = fopen(filename, "rb");
    if(filePtr == NULL)
    {
        return false;
    }

    // Read the two first bytes we don't need.
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

    // Which type of image gets stored in imageTypeCode.
    fread(&tgaFile->imageTypeCode, sizeof(unsigned char), 1, filePtr);

    // For our purposes, the type code should be 2 (uncompressed RGB image)
    // or 3 (uncompressed black-and-white images).
    if (tgaFile->imageTypeCode != 2 && tgaFile->imageTypeCode != 3)
    {
        fclose(filePtr);
        return false;
    }

    // Read 13 bytes of data we don't need.
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);

    // Read the image's width and height.
    fread(&tgaFile->imageWidth, sizeof(short int), 1, filePtr);
    fread(&tgaFile->imageHeight, sizeof(short int), 1, filePtr);

    // Read the bit depth.
    fread(&tgaFile->bitCount, sizeof(unsigned char), 1, filePtr);

    // Read one byte of data we don't need.
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

    // Color mode -> 3 = BGR, 4 = BGRA.
    colorMode = tgaFile->bitCount / 8;
    imageSize = tgaFile->imageWidth * tgaFile->imageHeight * colorMode;

    // Allocate memory for the image data.
    tgaFile->imageData = (unsigned char*)malloc(sizeof(unsigned char)*imageSize);

    // Read the image data.
    fread(tgaFile->imageData, sizeof(unsigned char), imageSize, filePtr);

    // Change from BGR to RGB so OpenGL can read the image data.
    for (int imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
    {
        colorSwap = tgaFile->imageData[imageIdx];
        tgaFile->imageData[imageIdx] = tgaFile->imageData[imageIdx + 2];
        tgaFile->imageData[imageIdx + 2] = colorSwap;
    }

    fclose(filePtr);
    return true;
}

GLuint LoadTexture ( char* pfile, TGA* tga = NULL )
{
	GLuint tex = 0;
	bool isTga = false;
	string tmp;
	
	for ( int i = 0; pfile [ i ] != EOF; i++ )
	{
		tmp += pfile [ i ];
	}

	if ( tmp.find ( ".tga" ) != string::npos || tmp.find ( ".TGA" ) != string::npos )
	{
		isTga = true;
	}

	if ( !isTga )
	{
		tex = LoadRegImage ( pfile );
	} else {
		if ( !LoadTGATexture ( pfile, tga ) ) 
			return NULL;
		
		int format = NULL;

		if ( ( tga->bitCount / 8 ) == 3 )
		{
			format = GL_BGR;
		} else if ( ( tga->bitCount / 8 ) == 4 ) {
			format = GL_BGRA;
		}
		
		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &tex );
	 
		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, tex );
	 
		// Set the texture's stretching properties
	        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	 
		// Edit the texture object's image data using the information SDL_Surface gives us
			glTexImage2D( GL_TEXTURE_2D, 0, tga->bitCount / 8, tga->imageWidth, tga->imageHeight, 0, format,
				GL_UNSIGNED_BYTE, tga->imageData );
	}
	return tex;
}

//////////////////////////////////////////////////////
//									        		//
//			LOG IMPLEMENTATION						//
//											    	//
//////////////////////////////////////////////////////

Log::Log ( )
{
	filename = "Log.log";
	fileOBJ = fopen ( filename, "rb" );
}

Log::Log ( char* file )
{
	string* temp = new string ( file );
	temp += '.';
	temp += 'l';
	temp += 'o';
	temp += 'g';
	filename = temp->c_str ( );
	fileOBJ = fopen ( filename, "rb" );
}

Log::~Log ( )
{
	fclose ( fileOBJ );
}

const char* Log::Read ( )
{
	string temp;
	LoadFileContents ( filename, temp );
	return temp.c_str ( );
}

void Log::Writeln ( char* msg )
{
	string temp = string ( msg );
	temp += '\n';
	fprintf ( fileOBJ, temp.c_str ( ) ); 
}

void Log::Write ( char* msg )
{
	string temp = string ( msg );
	fprintf ( fileOBJ, temp.c_str ( ) ); 
}

const char* Log::getFileName ( )
{
	return filename;
}

FILE* Log::getFILE ( )
{
	return fileOBJ;
}
#include "Audio.h"
#include "FileUtillities.h"

Sound::Sound ( int _chan, int _samplerate, int _bps, int _size, float posX, float posY, float posZ ) : chan ( _chan ), samplerate ( _samplerate ), bps ( _bps ), size ( _size ), position ( posX, posY, posZ )
{
	alGenBuffers ( 1, &bufferID );

	if ( chan == 1 )
	{
		if ( bps == 8 )
		{
			format = AL_FORMAT_MONO8;
		} else {
			format = AL_FORMAT_MONO16;
		}
	} else {
		if ( bps == 8 )
		{
			format = AL_FORMAT_STEREO8;
		} else {
			format = AL_FORMAT_STEREO16;
		}
	}

	alBufferData ( bufferID, format, data, size, samplerate );
	alGenSources ( 1, &sourceID );
	alSourcei ( sourceID, AL_BUFFER, bufferID );

}

bool Sound::isBigEndian ( )
{
	int a = 1;
	return ! ( ( char* ) &a )[0];
}

int Sound::convertToInt ( char* buffer, int len )
{
	int a = 0;

	if ( !isBigEndian ( ) )
	{
		for ( int i = 0; i < len; i++ )
		{
			( ( char* ) &a ) [ i ] = buffer [ i ];
		}
	} else { 
		for ( int i = 0; i < len; i++ )
		{
			( ( char* ) &a ) [ 3 - i ] = buffer [ i ];
		}
	}
	return a;
}

char* Sound::LoadWav ( const char* fn )
{
	char buffer [ 4 ];
    ifstream in ( fn, ios::binary );
    in.read ( buffer,4 );
    
	if ( strncmp ( buffer, "RIFF", 4 ) !=0 )
    {
        std::cout << "this is not a valid WAVE file"  << std::endl;
        return NULL;
    }
 
	in.read ( buffer, 4 );
    in.read ( buffer, 4 );      //WAVE
    in.read ( buffer, 4 );      //fmt
    in.read ( buffer, 4 );      //16
    in.read ( buffer, 2 );      //1
    in.read ( buffer, 2 );

    chan = convertToInt ( buffer,2 );

    in.read (buffer, 4 );
    
	samplerate = convertToInt ( buffer, 4 );
    
	in.read ( buffer, 4 );
    in.read ( buffer, 2 );
    in.read ( buffer, 2 );
    
	bps = convertToInt ( buffer, 2 );
    
	in.read ( buffer, 4 );      //data
    in.read ( buffer, 4 );

    size=convertToInt ( buffer,4 );
    
	char* data = new char [ size ];
    
	in.read ( data,size );
    
	return data;
}



int CreateOpenALContext ( ALCcontext* context, ALCdevice* device )
{
	Log* logger = new Log ( "OpenAL" );
	device = alcOpenDevice ( NULL );
	
	if ( !device )
	{	logger->Write ( "Unable to connect to sound card" );
		return 0;
	}
	
	context = alcCreateContext ( device, NULL );

	if ( !context )
	{
		logger->Write ( "Unable to create Context" );
	}

	alcMakeContextCurrent ( context );

	logger->~Log ( );

	return 1;
}

void DestroyOpenALContext ( ALCcontext* context, ALCdevice* device )
{
	alcDestroyContext ( context );
    alcCloseDevice ( device );
}

void Sound::Play ( )
{
	alSourcePlay ( sourceID );
}

void Sound::setPosition ( float x, float y, float z )
{
	position.setX ( x );
	position.setY ( y );
	position.setZ ( z );
}

void Sound::UpdatePosition ( )
{
	alSource3f ( sourceID, AL_POSITION, position.getX ( ), position.getY ( ), position.getY ( ) );
    alSourcei ( sourceID, AL_LOOPING, AL_TRUE);
	float f[] = { 1, 0, 0, 0, 1, 0 };
	alListenerfv ( AL_ORIENTATION, f );
}

Sound::~Sound ( )
{
	alDeleteSources ( 1, &sourceID );
	alDeleteBuffers ( 1, &bufferID );
}
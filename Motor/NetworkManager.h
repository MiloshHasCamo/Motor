#ifndef NETWORKMANAGER_H_
#define NETWORKMANAGER_H_

#include <SDL_net.h>
#include <iostream>
#include "FileUtillities.h"

typedef char Buffer [ 256 ];

void error ( char* msg );
bool InitNetwork ( );
void QuitNetwork ( );


namespace NetworkIO
{
	class ClientSocket;

	enum BufferStates 
	{
		EMPTY,
		READING, 
		WRITING, 
		FULL
	};

	class NetworkMessage
	{
	protected:
		Buffer buffer;
		BufferStates state;
		void Reset ( );
		Log* log;
		
	public:
		NetworkMessage ( );
		virtual int NumberToLoad ( );
		virtual int NumberToUnload ( );
	
		void LoadBytes ( Buffer& inputBuffer, int n );
		void UnloadByte ( Buffer& destBuffer );
		void Finish ( );
	};

	class IPAddress
	{
	private:
		IPaddress m_IP; //ip address struct
		Log* log;
		
	public:
		IPAddress ( );
		IPAddress ( Uint16 port );
		IPAddress ( std::string host, Uint16 port );
		
		void SetIP ( IPaddress sdl_ip );
		bool OK ( ) const;
		IPaddress getIPAddress ( ) const;
		Uint32 getHost ( ) const;
		Uint16 getPort ( ) const;
	};

	class TCPSocket 
	{
	protected:
		TCPsocket m_Socket;
		SDLNet_SocketSet set;
		Log* log;
		
	public:
		TCPSocket ( );
		virtual ~TCPSocket ( );
		virtual void setSocket ( TCPsocket socket );
		bool OK ( ) const;
		bool Ready ( ) const;
		virtual void OnReady ( ); //pure virtual		
	};

	class HostSocket: public TCPSocket
	{
	public:
		HostSocket ( IPAddress& ip ); 
		Log* log;
		
		HostSocket ( Uint16 port );
		bool Accept ( ClientSocket& socket );
		virtual void OnReady ( ); //pure virtual
	};

	class ClientSocket: public TCPSocket
	{
	private:
		IPAddress m_RemoteIP;
		Log* log;
		
	public:
		ClientSocket ( );
		ClientSocket ( std::string host, Uint16 port );
		
		bool Connect ( IPAddress& remoteIP );
		bool Connect ( HostSocket& socket );
		bool Receive ( NetworkMessage& rData );
		bool Send    ( NetworkMessage& sData );

		IPaddress getAddress ( void ) const;
		virtual void OnReady ( );
		void setSocket ( TCPsocket socket );
	};
}

#endif//NETWORKMANAGER_H_
#include "NetworkManager.h"
#include "FileUtillities.h"

static void error ( char* msg )
{
	perror ( msg );
	exit ( 0 );
}

bool InitNetwork ( )
{
	Log *log = new Log ( "NetworkLog" );
	if ( SDLNet_Init ( ) < 0 )
		log->Writeln ( "Initializtion problem" );
		log->~Log ( );
		return false;
	log->~Log ( );
	return true;
}

void QuitNetwork ( )
{
	SDLNet_Quit ( );
}

NetworkIO::NetworkMessage::NetworkMessage ( )
{
	Reset ( );
	log = new Log ( "NetworkLog" );
}

void NetworkIO::NetworkMessage::Reset ( )
{
	for ( int i = 0; i < 256; i++ )
		buffer [ i ] = 0;
	state = EMPTY;
}

void NetworkIO::NetworkMessage::Finish ( )
{
	if ( state == READING )
		state = FULL;
}

int NetworkIO::NetworkMessage::NumberToLoad ( )
{
	if ( state == EMPTY )
		return 255;
	return 0;
}

int NetworkIO::NetworkMessage::NumberToUnload ( )
{
	if ( state == FULL )
		return strlen ( buffer ) + 1;
	return 0;
}

void NetworkIO::NetworkMessage::LoadBytes ( Buffer& inputBuffer, int n )
{
	for ( int i = 0; i < n; i++ )
	{
		buffer [ i ] = inputBuffer [ i ];
	}
	state = READING;
}

void NetworkIO::NetworkMessage::UnloadByte ( Buffer& destBuf )
{
	for ( int i = 0; i < this->NumberToLoad ( ); i++ )
		destBuf [ i ] = buffer [ i ];
	Reset ( );
}

NetworkIO::IPAddress::IPAddress ( Uint16 port )
{
	if ( SDLNet_ResolveHost ( &m_IP, NULL, port ) < 0 )
	{
		log->Writeln ( "Error Resolving Host" );
		m_IP.host = 0;
		m_IP.port = 0;
	}
	log = new Log ( "NetworkLog" );
}

NetworkIO::IPAddress::IPAddress ( std::string host, Uint16 port )
{
	if ( SDLNet_ResolveHost ( &m_IP, host.c_str(), port ) < 0 ) 
	{
        std::cerr << "SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
        m_IP.host = 0;
        m_IP.port = 0;
    }
	log = new Log ( "NetworkLog" );
}

NetworkIO::IPAddress::IPAddress ( void )
{
	m_IP.host = 0;
	m_IP.port = 0;
	log = new Log ( "NetworkLog" );
}

bool NetworkIO::IPAddress::OK ( ) const 
{
	return !( m_IP.port == 0 );
}

void NetworkIO::IPAddress::SetIP ( IPaddress sdl_ip ) 
{
	m_IP = sdl_ip;
}

IPaddress NetworkIO::IPAddress::getIPAddress ( ) const 
{
	return m_IP;
}

Uint32 NetworkIO::IPAddress::getHost ( ) const 
{
	return m_IP.host;
}

Uint16 NetworkIO::IPAddress::getPort ( ) const 
{
	return m_IP.port;
}

NetworkIO::TCPSocket::TCPSocket ( )
{
	m_Socket = 0;
	set = SDLNet_AllocSocketSet ( 1 );
	log = new Log ( "NetworkLog" );
}

NetworkIO::TCPSocket::~TCPSocket ( ) 
{
	if ( ! ( m_Socket == NULL ) )
	{
		SDLNet_TCP_DelSocket ( set, m_Socket );
		SDLNet_FreeSocketSet ( set );
		SDLNet_TCP_Close ( m_Socket );
	}
}

void NetworkIO::TCPSocket::setSocket ( TCPsocket socket ) 
{
	if ( ! ( m_Socket == NULL ) )
	{
		SDLNet_TCP_DelSocket ( set, m_Socket );
		SDLNet_TCP_Close ( m_Socket );
	}
	
	m_Socket = socket;
	
	if ( SDLNet_TCP_AddSocket ( set, m_Socket ) == -1 )
	{
		std::cerr << "Error Creating new socket: " << SDLNet_GetError ( ) << std::endl;
		m_Socket = NULL;
	}
}

bool NetworkIO::TCPSocket::OK ( ) const
{
	return ! ( m_Socket == NULL );
}

bool NetworkIO::TCPSocket::Ready ( ) const 
{
	bool rd = false;
	int numready = SDLNet_CheckSockets ( set, 0 );

	if ( numready == -1 )
		log->Writeln ( "Error Checking socket" );
	else 
		if ( numready )
			rd = SDLNet_SocketReady ( m_Socket );
	return rd;
}

void NetworkIO::TCPSocket::OnReady ( ) { }

void NetworkIO::HostSocket::OnReady ( ) { }

NetworkIO::HostSocket::HostSocket ( IPAddress& port )
{
	log = new Log ( "NetworkLog" );
	TCPSocket::TCPSocket ( );
	IPaddress iph = port.getIPAddress ( );

	if ( ! ( m_Socket = SDLNet_TCP_Open ( &iph ) ) )
		SDLNet_FreeSocketSet ( set );
		log->Writeln ( "Error initializing TCP" );
}

NetworkIO::HostSocket::HostSocket ( Uint16 port )
{
	log = new Log ( "NetworkLog" );
	IPAddress iplistener ( port );

	if ( !iplistener.OK ( ) )
		m_Socket = NULL;
	else
		TCPSocket::TCPSocket ( );
		IPaddress iph = iplistener.getIPAddress ( );

		if ( ! ( m_Socket = SDLNet_TCP_Open ( &iph ) ) )
			SDLNet_FreeSocketSet ( set );
			log->Writeln ( "Error Initializing TCP" );
}

bool NetworkIO::HostSocket::Accept ( ClientSocket& the_client_socket )
{
    TCPsocket cs;
    if ( ( cs = SDLNet_TCP_Accept ( m_Socket ) ) )
	{
        the_client_socket.setSocket ( cs );
        return true;
    }
    else
        return false;
}

NetworkIO::ClientSocket::ClientSocket ( ) 
{
	log = new Log ( "NetworkLog" );
	TCPSocket::TCPSocket ( );
}

NetworkIO::ClientSocket::ClientSocket ( std::string host, Uint16 port )
{
	IPAddress remoteIP ( host.c_str ( ), port );

	if ( !remoteIP.OK ( ) )
	{
		m_Socket = NULL;
	} else {
		TCPSocket::TCPSocket ( );
		Connect ( remoteIP );
	}
}

bool NetworkIO::ClientSocket::Connect ( HostSocket& socket )
{
	return false;
}

bool NetworkIO::ClientSocket::Connect ( IPAddress& remoteIP )
{
	TCPsocket tcp_socket;
	IPaddress ip = remoteIP.getIPAddress ( );

	if ( ( tcp_socket = SDLNet_TCP_Open ( &ip ) ) )
	{
		setSocket ( tcp_socket );
		return true;
	} else {
		std::cerr << "Error Initializing TCP: " << SDLNet_GetError ( ) << std::endl;
	}
	return true;
}

void NetworkIO::ClientSocket::setSocket ( TCPsocket socket )
{
	TCPSocket::setSocket ( socket );
	IPaddress* ips;

	if ( ( ips = SDLNet_TCP_GetPeerAddress ( m_Socket ) ) )
	{
		m_RemoteIP.SetIP ( *ips );
		Uint32 hbo = m_RemoteIP.getHost ( );
		Uint16 pbo = m_RemoteIP.getPort ( );
		log->Writeln ( "Client Connected" );
	} else {
		log->Writeln ( "Error Connecting to peer address" );
	}
}

IPaddress NetworkIO::ClientSocket::getAddress ( void ) const 
{
	return m_RemoteIP.getIPAddress ( );
}

bool NetworkIO::ClientSocket::Receive ( NetworkMessage& rData )
{
	if ( m_Socket == NULL )
		return false;
	Buffer buf;

	while ( rData.NumberToLoad ( ) > 0 )
	{
		if ( SDLNet_TCP_Recv ( m_Socket, buf, rData.NumberToLoad ( ) ) > 0 )
		{
			rData.LoadBytes ( buf, rData.NumberToLoad ( ) );
		} else {
			return false;
		}
	}

	rData.Finish ( );
	return true;
}

bool NetworkIO::ClientSocket::Send ( NetworkMessage& sData )
{
	if ( m_Socket == NULL )
		return false;
	Buffer buf;
	int len;

	while ( ( len = sData.NumberToUnload ( ) ) > 0 )
	{
		sData.UnloadByte ( buf );

		if ( SDLNet_TCP_Send ( m_Socket, ( void * ) buf, len ) < len )
		{
			log->Writeln ( "Error Sending Message" );
			return false;
		}
	}
	return true;
}

void NetworkIO::ClientSocket::OnReady ( void ) { }
#ifndef __DreamSock_H
#define __DreamSock_H

#include "DreamConsole.h"

#ifdef WIN32
	#pragma comment (lib,"ws2_32.lib")
	#pragma message ("Auto linking WinSock2 library")

	#include <winsock2.h>
#else
	#include <string.h>
	#include <netinet/in.h>
#endif

#include <stdio.h>
#include <stddef.h>

// Define SOCKET data type for UNIX (defined in WinSock for Win32)
// And socklen_t for Win32
#ifdef WIN32
	typedef int socklen_t;
#else
	typedef int SOCKET;

	#ifndef TRUE
	#define TRUE 1
	#endif
	#ifndef FALSE
	#define FALSE 0
	#endif
#endif

// Host types
#define DREAMSERVER				-1
#define DREAMCLIENT				0

// Connection protocols
#define DREAMSOCK_TCP				0
#define DREAMSOCK_UDP				1

// Connection states
#define DREAMSOCK_CONNECTING			0
#define DREAMSOCK_CONNECTED			1
#define DREAMSOCK_DISCONNECTING			2
#define DREAMSOCK_DISCONNECTED			4

// Error codes
#define DREAMSOCK_SERVER_ERROR			1
#define DREAMSOCK_CLIENT_ERROR			2

#ifdef WIN32
	#define DREAMSOCK_INVALID_SOCKET	INVALID_SOCKET
#else
	#define DreamSock_INVALID_SOCKET	-1
#endif

// System messages
// Note (for all messages - system and user):
// positive = sequenced message
// negative = un-sequenced message
#define DREAMSOCK_MES_CONNECT		-101
#define DREAMSOCK_MES_DISCONNECT	-102
#define DREAMSOCK_MES_ADDCLIENT		-103
#define DREAMSOCK_MES_REMOVECLIENT	-104
#define DREAMSOCK_MES_PING		-105

class DreamWinSock;

class DreamSock
{
public:

	DreamSock();
	~DreamSock();


// Function prototypes
int	DreamSock_Initialize(void);
void 	DreamSock_Shutdown(void);

SOCKET DreamSock_Socket(int protocol);
int 	DreamSock_SetNonBlocking(SOCKET sock, u_long setMode);
int 	DreamSock_SetBroadcasting(SOCKET sock, int mode);
int 	DreamSock_StringToSockaddr(char *addressString, struct sockaddr *sadr);
SOCKET 	DreamSock_OpenUDPSocket(char netInterface[32], int port);
void 	DreamSock_CloseSocket(SOCKET sock);

int 	DreamSock_GetPacket(SOCKET sock, char *data, struct sockaddr *from);
void 	DreamSock_SendPacket(SOCKET sock, int length, char *data, struct sockaddr addr);
void 	DreamSock_Broadcast(SOCKET sock, int length, char *data, int port);

bool          dreamSock_init;
DreamWinSock* dreamWinSock;

#ifndef WIN32
int DreamSock_Linux_GetCurrentSystemTime(void);
#else
//int DreamSock_Win_GetCurrentSystemTime(void);
#endif

int DreamSock_GetCurrentSystemTime(void);

};
#endif

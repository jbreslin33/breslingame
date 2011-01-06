#ifndef __DREAMSERVER_H
#define __DREAMSERVER_H

#include "dreamConsole.h"

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

#define DREAMSOCK_MES_PING			-105

// Introduce classes
class dreamClient;
class dreamSock;
class dreamMessage;

class dreamServer
{
private:
	void			SendAddClient(dreamClient *newClient);
	void			SendRemoveClient(dreamClient *client);
	void			AddClient(struct sockaddr *address, char *name);
	void			RemoveClient(dreamClient *client);
	void			ParsePacket(dreamMessage *mes, struct sockaddr *address);
	int				CheckForTimeout(char *data, struct sockaddr *from);

	dreamClient		*clientList;

	int				port;					// Port
	SOCKET			socket;					// Socket
	int				runningIndex;			// Running index numbers for new clients

	bool			init;

public:
					dreamServer();
					~dreamServer();

	int				Initialise(char *localIP, int serverPort);
	void			Uninitialise(void);
	void			SendPing(void);
	int				GetPacket(char *data, struct sockaddr *from);
	void			SendPackets(void);

	bool			GetInit(void)			{ return init; }
	dreamClient		*GetClientList(void)	{ return clientList; }

	int				GetPort(void)			{ return port; }
};

#endif

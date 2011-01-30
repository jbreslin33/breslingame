#ifndef SERVERSIDECLIENT_H
#define SERVERSIDECLIENT_H

#include "Client.h"

#include "../dreamsock/DreamSock.h"
//#include "../dreamsock/DreamClient.h"
#include "../command/ServerSideCommand.h"

class DreamClient;

class ServerSideClient : public Client
{

public:
ServerSideClient();
~ServerSideClient();


	ServerSideCommand  frame[COMMAND_HISTORY_SIZE];
        ServerSideCommand  serverFrame;
        ServerSideCommand  command;

	long 		processedFrame;
	struct sockaddr address;
	DreamClient* 	netClient;
	
	ServerSideClient* next;
};

#endif

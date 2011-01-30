#ifndef CLIENTSIDECLIENT_H
#define CLIENTSIDECLIENT_H

#include "Client.h"

#include "../dreamsock/DreamSock.h"
//#include "../dreamsock/DreamClient.h"
#include "../command/ClientSideCommand.h"

class DreamClient;

class ClientSideClient : public Client
{

public:
ClientSideClient();
~ClientSideClient();

        ClientSideCommand  frame[COMMAND_HISTORY_SIZE];
        ClientSideCommand  serverFrame;
        ClientSideCommand  command;

	long 		processedFrame;
	struct sockaddr address;
	DreamClient* 	netClient;
	
	ClientSideClient* next;
};

#endif

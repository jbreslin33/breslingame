#ifndef CLIENTSIDECLIENT_H
#define CLIENTSIDECLIENT_H

#include "Client.h"

#include "Ogre.h"

#include "../dreamsock/DreamSock.h"
#include "../command/ClientSideCommand.h"

using namespace Ogre;

class DreamClient;
class Shape;

class ClientSideClient : public Client
{

public:
ClientSideClient();
~ClientSideClient();

        ClientSideCommand  frame[64];
        ClientSideCommand  serverFrame;
        ClientSideCommand  command;

	char password[30];
	int index;
	
	Shape* mShape;
	ClientSideClient* next;
};

#endif

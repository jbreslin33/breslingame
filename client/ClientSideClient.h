#ifndef CLIENTSIDECLIENT_H
#define CLIENTSIDECLIENT_H

#include "Client.h"

#include "Ogre.h"

#include "../dreamsock/DreamSock.h"
//#include "../dreamsock/DreamClient.h"
#include "../command/ClientSideCommand.h"

using namespace Ogre;

class DreamClient;

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
	Ogre::SceneNode *myNode;
	
	ClientSideClient* next;
};

#endif

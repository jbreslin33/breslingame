#ifndef CLIENTSIDENETWORK_H
#define CLIENTSIDENETWORK_H

#include "network.h"

class ClientSideGame;

class ClientSideNetwork : public Network
{
public:

ClientSideNetwork(ClientSideGame* clientSideGame);
~ClientSideNetwork();

ClientSideGame* mClientSideGame;

};
#endif

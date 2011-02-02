#ifndef CLIENTSIDENETWORK_H
#define CLIENTSIDENETWORK_H

#include "network.h"

class BaseGame;

class ClientSideNetwork : public Network
{
public:

ClientSideNetwork(BaseGame* baseGame);
~ClientSideNetwork();

BaseGame* mBaseGame;

};
#endif

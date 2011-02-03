#ifndef CLIENTSIDENETWORK_H
#define CLIENTSIDENETWORK_H

#include "network.h"

class BaseGame;
class DreamClient;

class ClientSideNetwork : public Network
{
public:

ClientSideNetwork(BaseGame* baseGame);
~ClientSideNetwork();

void	ReadPackets(void);

BaseGame* mBaseGame;
DreamClient* networkClient;


};
#endif

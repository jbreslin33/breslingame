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

void	ReadPackets		(void);
void	SendCommand		(void);
void	SendRequestNonDeltaFrame(void);

BaseGame* mBaseGame;
DreamClient* networkClient;


};
#endif

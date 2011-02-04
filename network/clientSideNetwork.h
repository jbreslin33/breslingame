#ifndef CLIENTSIDENETWORK_H
#define CLIENTSIDENETWORK_H

#include "network.h"

class BaseGame;
class DreamClient;
class DreamMessage;
class ClientSideClient;

class ClientSideNetwork : public Network
{
public:

ClientSideNetwork(BaseGame* baseGame);
~ClientSideNetwork();

void	ReadPackets		(void);
void	SendCommand		(void);
void	SendRequestNonDeltaFrame(void);
void	ReadMoveCommand         (DreamMessage *mes, ClientSideClient *client);
void	ReadDeltaMoveCommand    (DreamMessage *mes, ClientSideClient *client);
void	BuildDeltaMoveCommand   (DreamMessage *mes, ClientSideClient *theClient);

BaseGame* mBaseGame;
DreamClient* networkClient;


};
#endif

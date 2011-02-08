#ifndef CLIENTSIDENETWORK_H
#define CLIENTSIDENETWORK_H

#include "network.h"

class BaseGame;
class DreamClient;
class DreamMessage;
class ClientSideClient;
class ClientSideGame;

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

void	StartConnection		(const char serverIP[32]);
void	Connect			(void);
void	Disconnect		(void);
void	SendStartGame		(void);

BaseGame* mBaseGame;
DreamClient* networkClient;

ClientSideGame* mClientSideGame;

bool init;

};
#endif

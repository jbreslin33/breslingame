#ifndef CLIENTSIDENETWORK_H
#define CLIENTSIDENETWORK_H

#include "network.h"
#include "../client/ClientSideClient.h"
#include "../dreamsock/DreamMessage.h"

typedef struct clientLoginData
{
        int                                     index;
        char                            nickname[30];
        clientLoginData *next;
} clientLoginData;

extern char serverIP[32];


class ClientSideNetwork : public Network
{
public:

ClientSideNetwork();
~ClientSideNetwork();

// Network.cpp
void ReadPackets(void);
void SendCommand(void);
void SendRequestNonDeltaFrame(void);
void ReadMoveCommand(DreamMessage *mes, ClientSideClient *client);
void ReadDeltaMoveCommand(DreamMessage *mes, ClientSideClient *client);
void BuildDeltaMoveCommand(DreamMessage *mes, ClientSideClient *theClient);

        // Network.cpp
        void    StartConnection();
        void    Connect(void);
        void    Disconnect(void);
        void    SendStartGame(void);


};
#endif

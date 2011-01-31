#ifndef NETWORK_H
#define NETWORK_H

#include "../dreamsock/DreamSock.h"

class DreamClient;
class DreamMessage;
class ServerSideClient;
class Server;

#define COMMAND_HISTORY_SIZE            64

#define KEY_UP                                          1
#define KEY_DOWN                                        2
#define KEY_LEFT                                        4
#define KEY_RIGHT                                       8

#define CMD_KEY                                         1
#define CMD_ORIGIN                                      4

#define USER_MES_FRAME                          1
#define USER_MES_NONDELTAFRAME          2
#define USER_MES_SERVEREXIT                     3

typedef struct clientLoginData
{
        struct sockaddr         address;
        DreamClient                     *netClient;
        clientLoginData         *next;
} clientLoginData;


class Network
{

public:
Network(Server* server);
~Network();

void ReadPackets(void);
void SendCommand(void);
void SendExitNotification(void);
void ReadDeltaMoveCommand(DreamMessage *mes, ServerSideClient *client);
void BuildMoveCommand(DreamMessage *mes, ServerSideClient *client);
void BuildDeltaMoveCommand(DreamMessage *mes, ServerSideClient *client);

Server* mServer;

};
#endif

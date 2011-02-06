#ifndef SERVERSIDEGAME_H
#define SERVERSIDEGAME_H

#include "game.h"

#include <string.h>

class ServerSideCommand;
class ServerSideClient;
class DreamServer;
class ServerSideNetwork;

class ServerSideGame : public Game
{
public:
ServerSideGame();
~ServerSideGame();

int               InitNetwork();
void    	  ShutdownNetwork  (void);
void    	  CalculateVelocity(ServerSideCommand *command, float frametime);
void              MovePlayers      (void);
void    	  MovePlayer       (ServerSideClient *client);
void    	  AddClient        (void);
void    	  RemoveClient	   (struct sockaddr *address);
void   		  RemoveClients    (void);
void    	  Frame            (int msec);

ServerSideClient* GetClientList	   (void)   { return clientList; }

void    	 SetIndex          (int ind)       { index = ind; }
int              GetIndex          (void)          { return index; }

ServerSideNetwork* network;
DreamServer*       networkServer;
ServerSideGame*    next;
ServerSideClient*  clientList;            // Client list

int                clients;                                // Number of clients
int                realtime;                               // Real server up-time in ms
int                servertime;                             // ServerSideGame frame * 100 ms
float              frametime;                              // Frame time in seconds
int                index;
long               framenum;

};
#endif

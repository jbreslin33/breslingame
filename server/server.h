#ifndef SERVER_H
#define SERVER_H

#include <string.h>

class ServerSideCommand;
class ServerSideClient;
class DreamServer;
class Network;

class Server
{
public:
Server();
~Server();


int              InitNetwork();
void    	 ShutdownNetwork  (void);
void    	 CalculateVelocity(ServerSideCommand *command, float frametime);
void             MovePlayers      (void);
void    	 MovePlayer       (ServerSideClient *client);
void    	 AddClient        (void);
void    	 RemoveClient	  (struct sockaddr *address);
void   		 RemoveClients    (void);
void    	 Frame            (int msec);

ServerSideClient *GetClientList	  (void)   { return clientList; }

void    	 SetName          (char *n)                { strcpy(gamename, n); }
char    	 *GetName         (void)                  { return gamename; }
void    	 SetIndex         (int ind)       { index = ind; }
int              GetIndex         (void)          { return index; }


	Network* network;
        DreamServer     *networkServer;
        Server *next;


        ServerSideClient        *clientList;            // Client list
        int             clients;                                // Number of clients

        int             realtime;                               // Real server up-time in ms
        int             servertime;                             // Server frame * 100 ms
        float   frametime;                              // Frame time in seconds

        char    gamename[32];
        int             index;

        ServerSideClient *playerWithFlag;

        long    framenum;



};
#endif

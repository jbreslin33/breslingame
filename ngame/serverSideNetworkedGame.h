#ifndef SERVERSIDENETWORKEDGAME_H
#define SERVERSIDENETWORKEDGAME_H

#include "serverSideGame.h"
#include "../client/serverSideNetworkedClient.h"

class ServerSideNetworkedGame : public ServerSideGame
{

public:
	ServerSideNetworkedGame();
	~ServerSideNetworkedGame();

	dreamServer	*networkServer;
	ServerSideNetworkedClient	*clientList;		// Client list
	int		clients;				// Number of clients

	int		realtime;				// Real server up-time in ms
	int		servertime;				// Server frame * 100 ms
	float	frametime;				// Frame time in seconds

	char	gamename[32];
	int		index;
	long	framenum;
	int		InitNetwork();
	void	ReadPackets(void);

	void	ReadDeltaMoveCommand(dreamMessage *mes, ServerSideNetworkedClient *client);
	void	BuildMoveCommand(dreamMessage *mes, ServerSideNetworkedClient *client);
	void	BuildDeltaMoveCommand(dreamMessage *mes, ServerSideNetworkedClient *client);

	void	SendCommand(void);
	void	SendExitNotification(void);
	
	void	ShutdownNetwork(void);
	void	CalculateVelocity(ServerSideCommand *command, float frametime);
	void	MovePlayers(void);
	void	MovePlayer(ServerSideNetworkedClient *client);
	void	AddClient(void);
	void	RemoveClient(struct sockaddr *address);
	void	RemoveClients(void);


	ServerSideNetworkedClient *GetClientList(void)	{ return clientList; }
	void Frame(int msec);

	void	SetName(char *n)		{ strcpy(gamename, n); }
	char	*GetName(void)			{ return gamename; }

	void	SetIndex(int ind)	{ index = ind; }
	int		GetIndex(void)		{ return index; }

};

#endif

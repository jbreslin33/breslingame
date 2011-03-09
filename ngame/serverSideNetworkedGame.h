#ifndef SERVERSIDENETWORKEDGAME_H
#define SERVERSIDENETWORKEDGAME_H

#include "serverSideGame.h"


typedef struct clientLoginData
{
	struct sockaddr		address;
	dreamClient			*netClient;
	clientLoginData		*next;
} clientLoginData;

typedef struct
{
	float x;
	float y;
} VECTOR2D;

typedef struct
{
	int key;								// Pressed keys

	VECTOR2D vel;							// Velocity
	VECTOR2D origin;						// Position

	int msec;								// How long to run command (in ms)

} command_t;

typedef struct clientData
{
	command_t frame[COMMAND_HISTORY_SIZE];
	command_t serverFrame;
	command_t command;

	long processedFrame;

	struct sockaddr address;
	dreamClient *netClient;

	VECTOR2D startPos;
	bool team;

	clientData *next;
} clientData;



class ServerSideNetworkedGame : public ServerSideGame
{

public:
	ServerSideNetworkedGame();
	~ServerSideNetworkedGame();

	dreamServer	*networkServer;
	clientData	*clientList;		// Client list
	int		clients;				// Number of clients

	int		realtime;				// Real server up-time in ms
	int		servertime;				// Server frame * 100 ms
	float	frametime;				// Frame time in seconds

	char	gamename[32];
	int		index;
	long	framenum;
	int		InitNetwork();
	void	ReadPackets(void);

	void	ReadDeltaMoveCommand(dreamMessage *mes, clientData *client);
	void	BuildMoveCommand(dreamMessage *mes, clientData *client);
	void	BuildDeltaMoveCommand(dreamMessage *mes, clientData *client);

	void	SendCommand(void);
	void	SendExitNotification(void);
	
	void	ShutdownNetwork(void);
	void	CalculateVelocity(command_t *command, float frametime);
	void	MovePlayers(void);
	void	MovePlayer(clientData *client);
	void	AddClient(void);
	void	RemoveClient(struct sockaddr *address);
	void	RemoveClients(void);


	clientData *GetClientList(void)	{ return clientList; }
	void Frame(int msec);

	void	SetName(char *n)		{ strcpy(gamename, n); }
	char	*GetName(void)			{ return gamename; }

	void	SetIndex(int ind)	{ index = ind; }
	int		GetIndex(void)		{ return index; }

};

#endif

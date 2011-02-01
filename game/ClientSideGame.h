#ifndef CLIENTSIDEGAME_H
#define CLIENTSIDEGAME_H

#include "game.h"
#include "../math/Vector3D.h"
#include "../command/ClientSideCommand.h"
#include "../client/ClientSideClient.h"

//#include "Tutorial4.h"
class DreamMessage;
class DreamClient;
class ClientSideNetwork;
class BaseGame;

#ifdef WIN32
        //do nothing
#else

#define VK_ESCAPE 0     
#define VK_DOWN 1
#define VK_UP 2
#define VK_LEFT 3
#define VK_RIGHT 4
#define VK_SPACE 5
#endif

// The main application class interface
class ClientSideGame : public Game
{
public:
	void	DrawMap(void);
	
	void	CheckPredictionError(int a);
	void	CalculateVelocity(ClientSideCommand *command, float frametime);
	void	PredictMovement(int prevFrame, int curFrame);
	void	MoveObjects(void);

	void	AddClient(int local, int index, char *name);
	void	RemoveClient(int index);
	void	RemoveClients(void);

	DreamClient *networkClient;
	ClientSideNetwork* mClientSideNetwork;

	ClientSideClient *clientList;			// Client list
	ClientSideClient *localClient;		// Pointer to the local client in the client list
	int clients;

	ClientSideClient inputClient;			// Handles all keyboard input

	float frametime;

	char gamename[32];
	bool init;

	int gameIndex;

	ClientSideGame(BaseGame* baseGame);
	~ClientSideGame();

	void	Shutdown(void);
	void	CheckKeys(void);
	void	Frame(void);
	
	void	SetName(char *n)		{ strcpy(gamename, n); }
	char	*GetName(void)			{ return gamename; }

	void	SetGameIndex(int index)	{ gameIndex = index; }
	int		GetGameIndex(void)		{ return gameIndex; }

	ClientSideClient *GetClientList(void) { return clientList; }

	ClientSideClient *GetClientPointer(int index);

	ClientSideGame *next;

	BaseGame* mBaseGame;
};

#endif

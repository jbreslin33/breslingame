#ifndef CLIENTSIDEGAME_H
#define CLIENTSIDEGAME_H

#include "game.h"
#include "../client/ClientSideClient.h"

class BaseGame;
class ClientSideCommand;
class ClientSideNetwork;


class ClientSideGame : public Game
{
public:
	ClientSideGame(BaseGame* baseGame);
	~ClientSideGame();


	// Client.cpp
	void	CheckPredictionError(int a);
	void	CalculateVelocity(ClientSideCommand *command, float frametime);
	void	PredictMovement(int prevFrame, int curFrame);
	void	MoveObjects(void);

	void	AddClient(int local, int index, char *name);
	void	RemoveClient(int index);
	void	RemoveClients(void);


	void	Shutdown(void);
	void	CheckKeys(void);
	void	Frame(void);
	void	RunNetwork(int msec);

	ClientSideClient *clientList;			// Client list
	ClientSideClient *localClient;		// Pointer to the local client in the client list

	ClientSideClient inputClient;			// Handles all keyboard input

	float frametime;

	ClientSideClient *GetClientList(void) { return clientList; }

	ClientSideClient *GetClientPointer(int index);

	ClientSideNetwork* mClientSideNetwork;

	BaseGame *next;

BaseGame* mBaseGame;
};

#endif

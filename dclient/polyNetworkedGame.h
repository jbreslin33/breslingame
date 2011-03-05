#ifndef POLYNETWORKEDGAME_H
#define POLYNETWORKEDGAME_H

#include "game.h"
#include "../tdreamsock/dreamSock.h"

// The main application class interface
class PolyNetworkedGame : public Game
{

public:
	    virtual void go(void);
private:
	// Methods

	// Client.cpp
	void	DrawMap(void);

	void	CheckPredictionError(int a);
	void	CalculateVelocity(command_t *command, float frametime);
	void	PredictMovement(int prevFrame, int curFrame);
	void	MoveObjects(void);
	void    MovePlayer(void);

	void	AddClient(int local, int index, char *name);
	void	RemoveClient(int index);
	void	RemoveClients(void);

	// Network.cpp
	void	ReadPackets(void);
	void	SendCommand(void);
	void	SendRequestNonDeltaFrame(void);
	void	ReadMoveCommand(dreamMessage *mes, clientData *client);
	void	ReadDeltaMoveCommand(dreamMessage *mes, clientData *client);
	void	BuildDeltaMoveCommand(dreamMessage *mes, clientData *theClient);

	bool processUnbufferedInput(const Ogre::FrameEvent& evt);


	// Variables

	// Network variables
	dreamClient *networkClient;



	char gamename[32];


public:
	PolyNetworkedGame();
	~PolyNetworkedGame();

    //void createPlayer(int index);
    virtual void createScene(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	// Client.cpp
	void	Shutdown(void);
	bool	CheckKeys(void);
	void	Frame(void);
	void	RunNetwork(int msec);

	// Network.cpp
	void	StartConnection(char* serverIP);
	void	Connect(void);
	void	Disconnect(void);
	void	SendStartGame(void);

	void	SetName(char *n)		{ strcpy(gamename, n); }
	char	*GetName(void)			{ return gamename; }

	void	SetGameIndex(int index)	{ gameIndex = index; }
	int		GetGameIndex(void)		{ return gameIndex; }

	clientData *GetClientList(void) { return clientList; }


};

#endif

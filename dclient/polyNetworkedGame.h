#ifndef POLYNETWORKEDGAME_H
#define POLYNETWORKEDGAME_H

#include "networkedGame.h"
#include "../tdreamsock/dreamSock.h"

// The main application class interface
class PolyNetworkedGame : public NetworkedGame
{

public:
	    virtual void go(void);
private:
	// Methods

	// Client.cpp
	void	DrawMap(void);

void Shutdown(void);

	void	PredictMovement(int prevFrame, int curFrame);


	void	AddClient(int local, int index, char *name);


	// Network.cpp






	// Variables





	char gamename[32];


public:
	PolyNetworkedGame();
	~PolyNetworkedGame();

    //void createPlayer(int index);
    virtual void createScene(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	// Client.cpp


	void	Frame(void);
	void	RunNetwork(int msec);

	// Network.cpp
	void	StartConnection(char* serverIP);

	void	SendStartGame(void);

	void	SetName(char *n)		{ strcpy(gamename, n); }
	char	*GetName(void)			{ return gamename; }

	void	SetGameIndex(int index)	{ gameIndex = index; }
	int		GetGameIndex(void)		{ return gameIndex; }

	clientData *GetClientList(void) { return clientList; }


};

#endif

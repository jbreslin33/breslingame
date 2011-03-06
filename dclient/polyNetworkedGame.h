#ifndef POLYNETWORKEDGAME_H
#define POLYNETWORKEDGAME_H

#include "networkedGame.h"
#include "../tdreamsock/dreamSock.h"

class PolyNetworkedGame : public NetworkedGame
{

public:
	
PolyNetworkedGame();
~PolyNetworkedGame();

	virtual void go(void);

	void AddClient(int local, int index, char *name);
	
	virtual void createScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	void Frame(void);
	void RunNetwork(int msec);

	void StartConnection(char* serverIP);

	void SendStartGame(void);
	clientData *GetClientList(void) { return clientList; }
};

#endif

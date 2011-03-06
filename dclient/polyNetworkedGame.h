#ifndef POLYNETWORKEDGAME_H
#define POLYNETWORKEDGAME_H

#include "networkedGame.h"
#include "../tdreamsock/dreamSock.h"

class PolyNetworkedGame : public NetworkedGame
{

public:
	
PolyNetworkedGame();
~PolyNetworkedGame();


	virtual void gameLoop();
	void AddClient(int local, int index, char *name);
	
	virtual void createScene(void);

	void Frame(void);

	void StartConnection(char* serverIP);

	void SendStartGame(void);
	clientData *GetClientList(void) { return clientList; }
};

#endif

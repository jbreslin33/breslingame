#ifndef SERVERSIDENETWORKEDGAME_H
#define SERVERSIDENETWORKEDGAME_H

#include "serverSideGame.h"

class ServerSideNetworkedGame : public ServerSideGame
{

public:
	ServerSideNetworkedGame();
	~ServerSideNetworkedGame();

	void	ReadPackets(void);

};

#endif

#ifndef NETOWORKEDGAME_H
#define NETOWORKEDGAME_H

#include "game.h"
#include "../tdreamsock/dreamSock.h"

class NetworkedGame : public Game
{
public:

NetworkedGame();
~NetworkedGame();

	void	ReadPackets(void);
	void	ReadDeltaMoveCommand(dreamMessage *mes, clientData *client);
	void	SendCommand(void);
	void	SendRequestNonDeltaFrame(void);
	void	ReadMoveCommand(dreamMessage *mes, clientData *client);

	void	CheckPredictionError(int a);

	void	Connect(void);
	void	Disconnect(void);

	void	BuildDeltaMoveCommand(dreamMessage *mes, clientData *theClient);
	// Network variables
	dreamClient *networkClient;
};
#endif
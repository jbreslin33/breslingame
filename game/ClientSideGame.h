#ifndef CLIENTSIDEGAME_H
#define CLIENTSIDEGAME_H

#include "game.h"

class CArmyWar;

class ClientSideGame : public Game
{
public:
	ClientSideGame(CArmyWar* cArmyWar);
	~ClientSideGame();
CArmyWar* mCArmyWar;
};

#endif

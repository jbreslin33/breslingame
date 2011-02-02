#ifndef CLIENTSIDEGAME_H
#define CLIENTSIDEGAME_H

#include "game.h"

class BaseGame;

class ClientSideGame : public Game
{
public:
	ClientSideGame(BaseGame* baseGame);
	~ClientSideGame();
BaseGame* mBaseGame;
};

#endif

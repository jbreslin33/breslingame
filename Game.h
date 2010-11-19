/*
-----------------------------------------------------------------------------
Filename:    Game.h
*/
#ifndef __Game_h_
#define __Game_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


class GameServer;

class Game
{

public:
	Game();
    	virtual ~Game(void);

	void        setGameServer(GameServer* gameServer) { mGameServer = gameServer; }
	GameServer* getGameServer()                       { return mGameServer;       }

protected:

GameServer* mGameServer;

};

#endif



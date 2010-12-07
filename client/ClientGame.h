/*
-----------------------------------------------------------------------------
Basic ClientGame class

to get use out of this you want to extend it for a client game or server game then extend that for
whatever your game is.

The game itself should be another class completely such as pacman.h etc...QuestionFactory.h

This should be left very generic and have lots of virtual functions and pointers that are set
down the inheritance chain.

Filename:    ClientGame.h
*/
#ifndef __ClientGame_h_
#define __ClientGame_h_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "../Game.h"

class ServerConnection;

class ClientGame : public Game
{

public:
	ClientGame();
    	virtual ~ClientGame(void);

	ServerConnection* getServerConnection() { return mServerConnection; }
	void              setServerConnection(ServerConnection* conn) { mServerConnection = conn; }



protected:

ServerConnection* mServerConnection;
};

#endif

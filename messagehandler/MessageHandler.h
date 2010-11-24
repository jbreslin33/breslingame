
/*
-----------------------------------------------------------------------------
Filename:    MessageHandler.h
*/
#ifndef __MessageHandler_h_
#define __MessageHandler_h_

#include <stdio.h>
#include <stdlib.h>
#include <string>

class Game;
class ListenServer;

class MessageHandler
{

public:
    MessageHandler();
    virtual ~MessageHandler(void);

	//Messaging
	virtual void translateMessage(std::string message);

	virtual void          setGame (Game* game  )   { mGame = game; }
	virtual Game*         getGame (            )   { return mGame; }

	//ListenServer
	virtual void          setListenServer (ListenServer* listenServer  )  { mListenServer = listenServer; }
	virtual ListenServer* getListenServer (                            )  { return mListenServer; }


protected:

	//Messaging
	char*         mMessage;
	
	//GameServer - this will be subclassed to fit a particular game
	Game*   mGame;

	//ListenServer - this will not probably be subclassed
	ListenServer* mListenServer;


};

#endif

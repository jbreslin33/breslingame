
/*
-----------------------------------------------------------------------------
Filename:    MessageHandler.h
*/
#ifndef __MessageHandler_h_
#define __MessageHandler_h_

#include <stdio.h>
#include <stdlib.h>
#include <string>

class GameServer;
class ListenServer;

class MessageHandler
{

public:
    MessageHandler();
    virtual ~MessageHandler(void);

	//Messaging
	virtual void translateMessage(std::string message);
	
	//GameServer
	virtual void          setGameServer   (GameServer*   gameServer    )  { mGameServer = gameServer; }
	virtual GameServer*   getGameServer   (                            )  { return mGameServer;       }	

	//ListenServer
	virtual void          setListenServer (ListenServer* listenServer  )  { mListenServer = listenServer; }
	virtual ListenServer* getListenServer (                            )  { return mListenServer; }


protected:

	//Messaging
	char*         mMessage;
	
	//GameServer - this will be subclassed to fit a particular game
	GameServer*   mGameServer;

	//ListenServer - this will not probably be subclassed
	ListenServer* mListenServer;


};

#endif

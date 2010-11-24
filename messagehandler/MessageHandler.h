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
class Talker;

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

        //Talker
        virtual void          setTalker       (Talker*       talker        ) { mTalker        = talker;      } 
        virtual Talker*       getTalker       (                            ) { return mTalker; }

        //are we looping ListenServer??
        void setListen(bool b) { mListen = b; }
        bool getListen() { return mListen; }

        void run();

protected:

        //Messaging
        char*         mMessage;

        //GameServer - this will be subclassed to fit a particular game
        Game*   mGame;

        //ListenServer - this will not probably be subclassed
        ListenServer* mListenServer;

	//to listen or not to listen
	bool mListen;

	//Talker
	Talker* mTalker;

	
};

#endif

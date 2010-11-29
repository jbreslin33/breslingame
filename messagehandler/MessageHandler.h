/*
-----------------------------------------------------------------------------
Filename:    MessageHandler.h
*/
#ifndef __MessageHandler_h_
#define __MessageHandler_h_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

class Client;
class Game;

class MessageHandler
{

public:
    MessageHandler(Game* game);
    virtual ~MessageHandler(void);

        //Messaging
        
	virtual void translateMessage(char p1[100]);
	virtual void translateMessage(char p1[100], char p2[100]);
	virtual void translateMessage(char p1[100], char p2[100], char p3[100]);
	virtual void translateMessage(char p1[100], char p2[100], char p3[100], char p4[100]);

	virtual void translateMessage(Client* client, char p1[100], char p2[100]);
	
	virtual void          setGame (Game* game  )   { mGame = game; }
        virtual Game*         getGame (            )   { return mGame; }


protected:

        //Messaging
        char*         mMessage;

        //GameServer - this will be subclassed to fit a particular game
        Game*   mGame;

	//Make a vector of function name and parameters
	std::vector<std::string> functionVector;

};

#endif

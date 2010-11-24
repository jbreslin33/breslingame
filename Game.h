/*
-----------------------------------------------------------------------------
Basic Game class

to get use out of this you want to extend it for a client game or server game then extend that for
whatever your game is.

The game itself should be another class completely such as pacman.h etc...QuestionFactory.h

This should be left very generic and have lots of virtual functions and pointers that are set
down the inheritance chain.

Filename:    Game.h
*/
#ifndef __Game_h_
#define __Game_h_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

class Client;
class MessageHandler;

class GameServer;

class Game
{

public:
	Game();
    	virtual ~Game(void);


	//Client
	virtual void    addNewClient        (Client*         client        )  { clientVector.push_back(client);   }

        //messages
        void            setMessageHandler   (MessageHandler* messageHandler)  { mMessageHandler = messageHandler; }
        MessageHandler* getMessageHandler   (                              )  { return mMessageHandler;           }
        
	//generic leaving and joining
        virtual  void   joinGame            (std::string userName, std::string ip, std::string port ) { }
        virtual  void   leaveGame           (std::string id                                   )       { }


	virtual void run();
protected:

        //Clients, server and clients could point to this? might as well right now.
        std::vector<Client*> clientVector;

        //Everybody needs a message handler 
        MessageHandler* mMessageHandler;


};

#endif

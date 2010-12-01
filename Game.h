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
class Login;
class ListenServer;
class Talker;
class MessageHandler;

class GameServer;

class Game
{

public:
	Game();
    	virtual ~Game(void);

	//ServerIP
	virtual void   setServerIP           (char* ip                     )   { mServerIP = ip;                  }
	virtual char*  getServerIP           (                             )   { return mServerIP;                } 
	
	//Client
	virtual void    addNewClient        (Client*         client        )  { clientVector.push_back(client);   }

	//Login
	virtual void          setLogin        (Login* login                )  { mLogin = login;                   }
	virtual Login*        getLogin        (                            )  { return mLogin;                    }

        //ListenServer
        virtual void          setListenServer (ListenServer* listenServer  )  { mListenServer = listenServer;     }
        virtual ListenServer* getListenServer (                            )  { return mListenServer;             }

        //Talker
        virtual void          setTalker       (Talker*       talker        ) { mTalker        = talker;           } 
        virtual Talker*       getTalker       (                            ) { return mTalker;                    }

        //MessageHandler
        void            setMessageHandler   (MessageHandler* messageHandler)  { mMessageHandler = messageHandler; }
        MessageHandler* getMessageHandler   (                              )  { return mMessageHandler;           }
        
        //are we looping ListenServer??
        void setListen(bool b) { mListen = b; }
        bool getListen() { return mListen; }

	virtual void    signUp(std::string username, std::string ip, unsigned int short port);
	
	//generic leaving and joining
        virtual  void   joinGame            (std::string userName, std::string ip, std::string port ) { }
        virtual  void   leaveGame           (std::string id                                   )       { }


	virtual void run();
protected:


	//ServerIP
	char* mServerIP;	

        //Clients, server and clients could point to this? might as well right now.
        std::vector<Client*> clientVector;

	//Login
	Login* mLogin;

	//ListenServer
	ListenServer* mListenServer;

	//Talker
	Talker* mTalker; 

	//MessageHandler 
        MessageHandler* mMessageHandler;

	//Listen or not
	bool mListen;

	
};

#endif

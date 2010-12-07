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

class ClientConnection;
class Login;
class Communication;

class Game
{

public:
        Game();
        virtual ~Game(void);
	
	//misc
	char* convertIntToCharStar(int number);
        
	//ServerIP
        virtual void   setServerIP           (char* ip                     )   { mServerIP = ip;                  }
        virtual char*  getServerIP           (                             )   { return mServerIP;                } 
        
        //Client
        virtual void    addNewClientConnection (ClientConnection* clientConnection)  { clientConnectionVector.push_back(clientConnection);   }

        //Login
        virtual void          setLogin        (Login* login                )  { mLogin = login;                   }
        virtual Login*        getLogin        (                            )  { return mLogin;                    }

        //ListenServer
        virtual void           setCommunication (Communication* communication  )  { mCommunication = communication;   }
        virtual Communication* getCommunication (                              )  { return mCommunication;            }
        
        //are we looping ListenServer??
        void setListen(bool b) { mListen = b; }
        bool getListen() { return mListen; }

        virtual void    signUp        (char* username, char* ip);
	virtual void    changeUserName(char* username, char* clientConnectionID);

        //generic leaving and joining
        virtual  void   joinGame            (std::string userName, std::string ip, std::string port ) { }
        virtual  void   leaveGame           (std::string id                                   )       { }

        virtual void run();

protected:

        //ServerIP
        char* mServerIP;        

        //Clients, server and clients could point to this? might as well right now.
        std::vector<ClientConnection*> clientConnectionVector;

        //Login
        Login* mLogin;

        //Communication 
        Communication* mCommunication;

        //Listen or not
        bool mListen;

        int clientIDCounter;    
};

#endif


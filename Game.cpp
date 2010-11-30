/*
-----------------------------------------------------------------------------
Filename:    Game.cpp
*/

#include "Game.h"
#include "listenserver/ListenServer.h"
#include "messagehandler/MessageHandler.h"
#include "client/Client.h"

#include <iostream>

//-------------------------------------------------------------------------------------
Game::Game()
{
}
//-------------------------------------------------------------------------------------
Game::~Game(void)
{
	mLogin          = NULL;
	mListenServer   = NULL;
	mTalker         = NULL;
	mMessageHandler = NULL;
	mListen         = NULL;
}

void Game::signUp(std::string username, std::string ip, std::string port)
{
	std::cout << "in signUp\n";

	//printf("clientVectorSize:%d",clientVector.size());

	bool nameTaken = false;

        //create a client so we can communicate without jumping thru hoops
        std::cout << "Create a client\n";
        Client* client = new Client(username);
        clientVector.push_back(client);

/*
	for (int i = 0; i < clientVector.size(); i++)
	{
		if (client == clientVector.at(i))
			continue;	

		if (clientVector.at(i)->getUserName().compare(username) == 0)
		{
			nameTaken = true;
		}		
	}

	if (nameTaken)
	{
		//tell user to try again
		std::cout << "tell user to try again....\n";
		getMessageHandler()->translateMessage(client, "toClient", "enterNewUserName");
	}
	else
	{
		//create a client
		std::cout << "Create a client\n";
		Client* client = new Client(username);
		clientVector.push_back(client);

	}
*/
}

void Game::run()
{
	mListenServer->processRequests();
}

/*
-----------------------------------------------------------------------------
Filename:    Game.cpp
*/

#include "Game.h"
#include "listenserver/ListenServer.h"
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

void Game::signUp(std::string username)
{
	std::cout << "in signUp\n";

		std::cout << "booooooooooooooogers....";
	bool nameTaken = false;

	for (int i = 0; clientVector.size(); i++)
	{
		if (clientVector.at(i)->getUserName().compare(username) == 0)
		{
			nameTaken = true;
		}		
	}

	if (nameTaken)
	{
		//tell user to try again
		std::cout << "tell user to try again....";
	}
	else
	{
		//create a client
		std::cout << "create a client";

	}

}

void Game::run()
{
	mListenServer->processRequests();
}


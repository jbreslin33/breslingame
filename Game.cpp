/*
-----------------------------------------------------------------------------
Filename:    Game.cpp
*/

#include "Game.h"
#include "communication/Communication.h"
#include "connection/ClientConnection.h"


#include <iostream>

//-------------------------------------------------------------------------------------
Game::Game()
{
}
//-------------------------------------------------------------------------------------
Game::~Game(void)
{
	mLogin          = NULL;
	mCommunication  = NULL;
}

void Game::signUp(std::string username, char* ip)
{
	std::cout << "in signUp\n";

	//printf("clientVectorSize:%d",clientVector.size());

	bool nameTaken = false;

        //create a client so we can communicate without jumping thru hoops
        std::cout << "Create a client\n";
        ClientConnection* clientConnection = new ClientConnection(username);
	clientConnection->setIP(ip);
        clientConnectionVector.push_back(clientConnection);


	for (int i = 0; i < clientConnectionVector.size(); i++)
	{
		if (clientConnection == clientConnectionVector.at(i))
			continue;	

		if (clientConnectionVector.at(i)->getUserName().compare(username) == 0)
		{
			nameTaken = true;
		}		
	}

	if (nameTaken)
	{
		//tell user to try again
		std::cout << "tell user to try again....\n";
	//	getMessageHandler()->translateMessage("toClient", "enterNewUserName", client->getIP());
	}
	else
	{
//		getCommunication()->send(clientConnection,"promptForChangeUserName",
		//create a client
		//std::cout << "Create a client\n";
		//ClientConnection* clientConnection = new ClientConnection(username);
		//clientConnectionVector.push_back(clientConnection);
		getCommunication()->send(clientConnection,"welcome");
	}

}

void Game::run()
{
	mCommunication->processRequests();
}

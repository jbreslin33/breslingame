/*
-----------------------------------------------------------------------------
Filename:    Game.cpp
*/

#include "Game.h"
#include "communication/Communication.h"
#include "connection/ClientConnection.h"


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
//-------------------------------------------------------------------------------------
Game::Game()
{
}
//-------------------------------------------------------------------------------------
Game::~Game(void)
{
        mLogin          = NULL;
        mCommunication  = NULL;
        clientIDCounter = 0;
	mClientConnectionID = NULL; 
}


void Game::changeUserName(char* username, char* clientConnectionID)
{
/*
	int id = atoi(clientConnectionID);
     	bool nameTaken = false;
	
	ClientConnection* clientConnection;

        for (int i = 0; i < clientConnectionVector.size(); i++)
	{
		if (clientConnectionVector.at(i)->getID() == id)
		{
			std::cout << "found client in vector";
			clientConnection = clientConnectionVector.at(i);
		} 
	}

        for (int i = 0; i < clientConnectionVector.size(); i++)
        {
                if (clientConnection == clientConnectionVector.at(i))
                        continue;

                if (strcmp(clientConnectionVector.at(i)->getUserName(),username) == 0)
                {
                        nameTaken = true;
                }
        }

        if (nameTaken)
        {
                //tell user to try again
                std::cout << "tell user to try again....\n";
	//	getCommunication()->send(clientConnection,"enterNewUserName"
        }
        else
        {
		clientConnection->setUserName(username);
                getCommunication()->send(clientConnection,"welcome");
        }
*/	
		
}

void Game::signUp(char* username, char* ip)
{

        bool nameTaken = false;

        //create a client so we can communicate without jumping thru hoops
        std::cout << "Create a client\n";
        ClientConnection* clientConnection = new ClientConnection(username);
        clientConnection->setIP(ip);
        clientConnection->setPort("38388");
        clientConnection->setID(clientIDCounter);
        clientIDCounter++;
	clientConnectionVector.push_back(clientConnection);

        for (int i = 0; i < clientConnectionVector.size(); i++)
        {
                if (clientConnection->getID() == clientConnectionVector.at(i)->getID())
		{
                 	//printf("continue\n");
	        	//continue;       
		}
		else if (strcmp(clientConnectionVector.at(i)->getUserName(),username) != 0)
               	{
                       	nameTaken = true;
                }               
        }

        if (nameTaken)
        {
                //tell user to try again
                std::cout << "tell user to try again....\n";
                getCommunication()->send(clientConnection,"enterDifferentUserName", convertIntToCharStar(clientConnection->getID()));
        }
        else
        {
                getCommunication()->send(clientConnection,"welcome", convertIntToCharStar(clientConnection->getID()));
        }

}

char* Game::convertIntToCharStar(int number)
{
	std::stringstream ss;//create a stringstream
   	ss << number;//add number to the stream
   	std::string tempString = ss.str();//return a string with the contents of the stream
	char* cstr;   
 	cstr = new char [tempString.size()+1];
  	strcpy (cstr, tempString.c_str());
	return cstr;
}
void Game::run()
{
        mCommunication->processRequests();
}



/*
-----------------------------------------------------------------------------
Filename:    MessageHandler.cpp
*/

#include "MessageHandler.h"
#include "../Game.h"
#include "../talker/Talker.h"


#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
//-------------------------------------------------------------------------------------
MessageHandler::MessageHandler(Game* game)
{
	//create ListenServer here as ListenServer has no need to be subclassed for different games.
	std::cout << "MessageHandler Constructor\n";

	mGame         = game;
	mMessage      = NULL;
}
//-------------------------------------------------------------------------------------
MessageHandler::~MessageHandler(void)
{
}

void MessageHandler::translateMessage(char p1[100], char p2[100])
{


}

void MessageHandler::translateMessage(char p1[100], char p2[100], char p3[100])
{
	if (strcmp(p1,"toServer") == 0)
	{
		std::cout << "going to send this message to server\n";
		char total[200];
		strcpy (total,"");
		strcat (total,p2);
		strcat (total,",");
		strcat (total,p3);
        	puts (total);

		mGame->getTalker()->sendMessageToServer(total);
	}
}


void MessageHandler::translateMessage(char p1[100], char p2[100], char p3[100], char p4[100])
{
}

void MessageHandler::translateMessage(Client* client, char p1[100], char p2[100])
{
	
}

/*this should call a function on the client or the server */

//this handles the info recieved from a client message buf,ip,port
void MessageHandler::translateMessage(char cstr[400], char* ip, unsigned short int port)
{

  	// cstr now contains a c-string copy of str
	char *p;

  	p=strtok (cstr,",");
  	while (p!=NULL)
  	{
    		std::cout << p << std::endl;
		functionVector.push_back(p);
    		p=strtok(NULL,",");
  	}

/**************check what function to call***************************/

	if (functionVector.at(0).compare("signUp") == 0)
	{	
		std::cout << "calling signUp(username)\n";
		             //username           , ip                 , port
		mGame->signUp(functionVector.at(1), ip , port);		
	}
	
	if (functionVector.at(0).compare("joingame") == 0)
	{	
		mGame->joinGame(functionVector.at(1),functionVector.at(2),functionVector.at(3));		
	}
	

	//server to client
	if (functionVector.at(0).compare("nameTaken") == 0)
	{
		//getGameServer()->joinGame(functionVector.at(1),functionVector.at(2),functionVector(3));		
	}

	functionVector.clear();


/************************end check what function***********/
}

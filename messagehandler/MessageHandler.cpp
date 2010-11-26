
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
	        //std::cout << ("p1:%s",p1);
		char total[200];
		strcpy (total,"");
		strcat (total,p2);
		strcat (total,",");
		strcat (total,p3);
	       // std::cout << ("p1:%s",p1);
        	puts (total);

	       // std::cout << ("p1:%s",p1);
		mGame->getTalker()->sendMessageToServer(total);
	}
}


void MessageHandler::translateMessage(char p1[100], char p2[100], char p3[100], char p4[100])
{
}

/*this should call a function on the client or the server */
void MessageHandler::translateMessage(char cstr[400])
{
	std::cout << "in translateMessage going to \n";
/*
	char * cstr, *p;

  	//std::string str ("Please,split,this,phrase,into,tokens");

  	cstr = new char [message.size()+1];
  	strcpy (cstr, message.c_str());
*/
  	// cstr now contains a c-string copy of str
	char *p;
	

  	p=strtok (cstr,",");
  	while (p!=NULL)
  	{
    		std::cout << p << std::endl;
		functionVector.push_back(p);
    		p=strtok(NULL,",");
  	}

  	//delete[] cstr;  

/**************check what function***************************/

	//client to server
std::cout << "here dog\n";

	if (functionVector.at(0).compare("signUp") == 0)
	{	
		std::cout << "calling signUp(username)\n";
		//mGame->signUp(functionVector.at(1));		
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

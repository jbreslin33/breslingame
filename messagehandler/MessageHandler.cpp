
/*
-----------------------------------------------------------------------------
Filename:    MessageHandler.cpp
*/

#include "MessageHandler.h"
#include "../Game.h"

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

/*this should call a function on the client or the server */
void MessageHandler::translateMessage(std::string message)
{
        std::string u = "username";


	char * cstr, *p;

  	//std::string str ("Please,split,this,phrase,into,tokens");

  	cstr = new char [message.size()+1];
  	strcpy (cstr, message.c_str());

  	// cstr now contains a c-string copy of str

  	p=strtok (cstr,",");
  	while (p!=NULL)
  	{
    		std::cout << p << std::endl;
		functionVector.push_back(p);
    		p=strtok(NULL,",");
  	}

  	delete[] cstr;  

/**************check what function***************************/

	//client to server


	if (functionVector.at(0).compare("signUp") == 0)
	{	
		std::cout << "calling signUp(username)\n";
		mGame->signUp(functionVector.at(1));		
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

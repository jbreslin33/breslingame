
/*
-----------------------------------------------------------------------------
Filename:    MessageHandler.cpp
*/

#include "MessageHandler.h"
#include "../listenserver/ListenServer.h"
#include "../talker/Talker.h"

#include <iostream>

//-------------------------------------------------------------------------------------
MessageHandler::MessageHandler()
{
	//create ListenServer here as ListenServer has no need to be subclassed for different games.
	std::cout << "MessageHandler Constructor\n";

	mGame         = NULL;
	mListenServer = new ListenServer();
	mTalker       = new Talker();	
	mMessage      = NULL;
	mListen       = false;
}
//-------------------------------------------------------------------------------------
MessageHandler::~MessageHandler(void)
{
}

/*this should call a function on the client or the server */


void MessageHandler::translateMessage(std::string message)
{
}

void MessageHandler::run()
{
	if (mListen == true)
	{
		mListenServer->processRequests();
	}

	
	
}


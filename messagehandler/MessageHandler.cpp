
/*
-----------------------------------------------------------------------------
Filename:    MessageHandler.cpp
*/

#include "MessageHandler.h"
#include "../listenserver/ListenServer.h"

#include <iostream>

//-------------------------------------------------------------------------------------
MessageHandler::MessageHandler()
{
	//create ListenServer here as ListenServer has no need to be subclassed for different games.
	std::cout << "MessageHandler Constructor\n";

	mGame         = NULL;
	mListenServer = new ListenServer();	
	mMessage      = NULL;
}
//-------------------------------------------------------------------------------------
MessageHandler::~MessageHandler(void)
{
}

/*this should call a function on the client or the server */


void MessageHandler::translateMessage(std::string message)
{
}

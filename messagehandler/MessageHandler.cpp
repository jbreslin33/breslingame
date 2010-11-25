
/*
-----------------------------------------------------------------------------
Filename:    MessageHandler.cpp
*/

#include "MessageHandler.h"

#include <iostream>

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

void MessageHandler::translateMessage(std::string message)
{
}

/*
-----------------------------------------------------------------------------
Filename:    Game.cpp
*/

#include "Game.h"
#include "messagehandler/MessageHandler.h"

//-------------------------------------------------------------------------------------
Game::Game()
{
	mMessageHandler = new MessageHandler();
	mMessageHandler->setListen(true);
	
	//let's start it all up....
	run();
}
//-------------------------------------------------------------------------------------
Game::~Game(void)
{
}

void Game::run()
{
	mMessageHandler->run();
	run();
}


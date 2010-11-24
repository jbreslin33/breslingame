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


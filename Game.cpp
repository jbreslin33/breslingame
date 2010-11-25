/*
-----------------------------------------------------------------------------
Filename:    Game.cpp
*/

#include "Game.h"
#include "listenserver/ListenServer.h"


#include <iostream>

//-------------------------------------------------------------------------------------
Game::Game()
{
}
//-------------------------------------------------------------------------------------
Game::~Game(void)
{
	mLogin          = NULL;
	mListenServer   = NULL;
	mTalker         = NULL;
	mMessageHandler = NULL;
	mListen         = NULL;
}

void Game::signUp(std::string username)
{
	std::cout << "in signUp\n";
}

void Game::run()
{
	mListenServer->processRequests();
	run();
}


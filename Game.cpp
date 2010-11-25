/*
-----------------------------------------------------------------------------
Filename:    Game.cpp
*/

#include "Game.h"
#include "listenserver/ListenServer.h"

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

void Game::run()
{
	mListenServer->processRequests();
	run();
}


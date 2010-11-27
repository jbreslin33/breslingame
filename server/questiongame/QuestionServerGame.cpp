/*
-----------------------------------------------------------------------------
Filename:    QuestionServerGame.cpp
*/

#include "QuestionServerGame.h"
#include "../../talker/Talker.h"
#include "../../messagehandler/MessageHandler.h"
#include "../../listenserver/ListenServer.h"



//-------------------------------------------------------------------------------------
QuestionServerGame::QuestionServerGame()
{
	mTalker         = new Talker(this);
	mMessageHandler = new MessageHandler(this);
	mListenServer   = new ListenServer(this);
}
//-------------------------------------------------------------------------------------
QuestionServerGame::~QuestionServerGame(void)
{
}



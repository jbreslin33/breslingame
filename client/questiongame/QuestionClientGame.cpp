/*
-----------------------------------------------------------------------------
Filename:    QuestionClientGame.cpp
*/

#include "QuestionClientGame.h"
#include "../login/Login.h"
#include "../../messagehandler/MessageHandler.h"
#include "../../listenserver/ListenServer.h"
#include "../../talker/Talker.h"

//-------------------------------------------------------------------------------------
QuestionClientGame::QuestionClientGame()
{
	mListenServer   = new ListenServer  (this,4951);
	mTalker         = new Talker        (this); //no harm in creating this now i guess
	mMessageHandler = new MessageHandler(this);
	mLogin          = new Login         (this);

	
}
//-------------------------------------------------------------------------------------
QuestionClientGame::~QuestionClientGame(void)
{
}



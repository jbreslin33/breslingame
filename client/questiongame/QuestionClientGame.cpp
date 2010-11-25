/*
-----------------------------------------------------------------------------
Filename:    QuestionClientGame.cpp
*/

#include "QuestionClientGame.h"
#include "../login/Login.h"
#include "../../messagehandler/MessageHandler.h"
#include "../../talker/Talker.h"

//-------------------------------------------------------------------------------------
QuestionClientGame::QuestionClientGame()
{
	mTalker = new Talker(this); //no harm in creating this now i guess
	mLogin = new Login(this);

	//mMessageHandler = new MessageHandler(this);
	
}
//-------------------------------------------------------------------------------------
QuestionClientGame::~QuestionClientGame(void)
{
}



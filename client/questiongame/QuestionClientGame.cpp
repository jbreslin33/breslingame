/*
-----------------------------------------------------------------------------
Filename:    QuestionClientGame.cpp
*/

#include "QuestionClientGame.h"
#include "../login/Login.h"
#include "../../messagehandler/MessageHandler.h"

//-------------------------------------------------------------------------------------
QuestionClientGame::QuestionClientGame()
{

	mLogin = new Login(this);

	//mMessageHandler = new MessageHandler(this);
	
}
//-------------------------------------------------------------------------------------
QuestionClientGame::~QuestionClientGame(void)
{
}



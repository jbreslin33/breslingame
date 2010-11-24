/*
-----------------------------------------------------------------------------
Filename:    QuestionClientGame.cpp
*/

#include "QuestionClientGame.h"
#include "../../messagehandler/MessageHandler.h"

//-------------------------------------------------------------------------------------
QuestionClientGame::QuestionClientGame()
{
	mMessageHandler->setListen(false);

}
//-------------------------------------------------------------------------------------
QuestionClientGame::~QuestionClientGame(void)
{
}



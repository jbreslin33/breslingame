/*
-----------------------------------------------------------------------------
Filename:    QuestionClientGame.cpp
*/

#include "QuestionClientGame.h"
#include "../login/Login.h"
#include "../../communication/Communication.h"
#include "../../connection/ServerConnection.h"

//-------------------------------------------------------------------------------------
QuestionClientGame::QuestionClientGame()
{
	mServerConnection = new ServerConnection();
	mServerConnection->setPort("38387"); 
	mCommunication    = new Communication   (this, "38388");
	mLogin            = new Login           (this);
}
//-------------------------------------------------------------------------------------
QuestionClientGame::~QuestionClientGame(void)
{
}



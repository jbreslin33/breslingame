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
	mCommunication  = new Communication (this, 38388);
	mLogin          = new Login         (this);
	mServerConnection = NULL; 
}
//-------------------------------------------------------------------------------------
QuestionClientGame::~QuestionClientGame(void)
{
}



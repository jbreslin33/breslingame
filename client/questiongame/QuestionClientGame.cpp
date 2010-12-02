/*
-----------------------------------------------------------------------------
Filename:    QuestionClientGame.cpp
*/

#include "QuestionClientGame.h"
#include "../login/Login.h"
#include "../../communication/Communication.h"

//-------------------------------------------------------------------------------------
QuestionClientGame::QuestionClientGame()
{
	mCommunication  = new Communication (this, 38387);
	mLogin          = new Login         (this);
}
//-------------------------------------------------------------------------------------
QuestionClientGame::~QuestionClientGame(void)
{
}



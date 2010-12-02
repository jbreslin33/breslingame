/*
-----------------------------------------------------------------------------
Filename:    QuestionServerGame.cpp
*/

#include "QuestionServerGame.h"
#include "../../communication/Communication.h"

//-------------------------------------------------------------------------------------
QuestionServerGame::QuestionServerGame()
{
	mCommunication   = new Communication(this, 38387);
}
//-------------------------------------------------------------------------------------
QuestionServerGame::~QuestionServerGame(void)
{
}



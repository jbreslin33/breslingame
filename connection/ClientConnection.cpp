/*
-----------------------------------------------------------------------------
Filename:    ClientConnection.cpp
*/

#include "ClientConnection.h"


//-------------------------------------------------------------------------------------
ClientConnection::ClientConnection(char* userName)
{
	mUserName = userName;
	mID = NULL;
}
//-------------------------------------------------------------------------------------
ClientConnection::~ClientConnection(void)
{
}



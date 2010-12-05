/*
-----------------------------------------------------------------------------
Filename:    ClientConnection.cpp
*/

#include "ClientConnection.h"


//-------------------------------------------------------------------------------------
ClientConnection::ClientConnection(std::string userName)
{
	mUserName = userName;
	mID = NULL;
}
//-------------------------------------------------------------------------------------
ClientConnection::~ClientConnection(void)
{
}



/*
-----------------------------------------------------------------------------
Filename:    ClientConnection.cpp
*/

#include "ClientConnection.h"


//-------------------------------------------------------------------------------------
ClientConnection::ClientConnection(std::string userName, char* ip) : Connection(ip)
{
	mUserName = userName;
}
//-------------------------------------------------------------------------------------
ClientConnection::~ClientConnection(void)
{
}



/*
-----------------------------------------------------------------------------
Filename:    ClientConnection.cpp
*/

#include "ClientConnection.h"


//-------------------------------------------------------------------------------------
ClientConnection::ClientConnection(std::string userName, std::string ip) : Connection(ip)
{
	mUserName = userName;
}
//-------------------------------------------------------------------------------------
ClientConnection::~ClientConnection(void)
{
}



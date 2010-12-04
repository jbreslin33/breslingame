/*
-----------------------------------------------------------------------------
Filename:    ClientConnection.h
*/
#ifndef __ClientConnection_h_
#define __ClientConnection_h_

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Connection.h"


class ClientConnection : public Connection
{

public:
    ClientConnection(std::string userName, char* ip);
    virtual ~ClientConnection(void);

	//username
	void        setUserName(std::string userName) { mUserName = userName; }
    	std::string getUserName(                    ) { return mUserName;     }


protected:

std::string mUserName;

};

#endif



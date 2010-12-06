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
    ClientConnection(char* userName);
    virtual ~ClientConnection(void);

	//username
	void        setUserName(char* userName) { mUserName = userName; }
    	char* getUserName(                    ) { return mUserName;     }

	void        setID(int id) { mID = id; }
	int         getID() { return mID; }

protected:

char* mUserName;
int mID;

};

#endif



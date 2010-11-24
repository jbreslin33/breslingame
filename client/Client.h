/*
-----------------------------------------------------------------------------
Filename:    Client.h
*/
#ifndef __Client_h_
#define __Client_h_

#include <stdio.h>
#include <stdlib.h>
#include <string>


class Client;

class Client
{

public:
    Client(std::string userName);
    virtual ~Client(void);

	//username
	void        setUserName(std::string userName) { mUserName = userName; }
    	std::string getUserName(                    ) { return mUserName;     }

protected:

std::string mUserName;

};

#endif



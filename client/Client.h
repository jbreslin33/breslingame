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
    Client(std::string userName, std::string ip);
    virtual ~Client(void);

	//username
	void        setUserName(std::string userName) { mUserName = userName; }
    	std::string getUserName(                    ) { return mUserName;     }

	std::string getIP      (                    ) { return mIP;           }
	void        setIP      (char* IP            ) { mIP = IP;             }

protected:

std::string mUserName;
std::string mIP;

};

#endif



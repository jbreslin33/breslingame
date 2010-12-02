/*
-----------------------------------------------------------------------------
Filename:    Connection.h
*/
#ifndef __Connection_h_
#define __Connection_h_

#include <stdio.h>
#include <stdlib.h>
#include <string>


class Connection
{

public:
    Connection(std::string ip);
    virtual ~Connection(void);

	std::string getIP      (                    ) { return mIP;           }
	void        setIP      (char* IP            ) { mIP = IP;             }

protected:

std::string mIP;

};

#endif



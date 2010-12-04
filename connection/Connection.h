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
    Connection(char* ip);
    virtual ~Connection(void);

	char*       getIP      (                    ) { return mIP;           }
	void        setIP      (char* IP            ) { mIP = IP;             }

protected:

char* mIP;

};

#endif



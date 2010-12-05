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
    Connection();
    virtual ~Connection(void);

	char*       getIP      (                    ) { return mIP;           }
	void        setIP      (char* IP            ) { mIP = IP;             }

	const char*       getPort    (                    ) { return mPort;           }
	void        setPort    (const char* port          ) { mPort = port;             }


protected:

char* mIP;
const char* mPort;
};

#endif



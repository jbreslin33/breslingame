/*
-----------------------------------------------------------------------------
Filename:    ServerConnection.h
*/
#ifndef __ServerConnection_h_
#define __ServerConnection_h_

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Connection.h"

class ServerConnection : public Connection
{

public:
    ServerConnection(std::string ip);
    virtual ~ServerConnection(void);


protected:


};

#endif



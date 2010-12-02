/*
-----------------------------------------------------------------------------
Filename:    Communication.h
*/
#ifndef __COMMUNICATION_h_
#define __COMMUNICATION_h_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstdlib>

#define MAXBUFLEN 100;
#define BUFLEN 512
#define NPACK 10

class Game;

class Communication
{

public:
    Communication(Game* game, short unsigned int port);
    virtual ~Communication(void);

	void  diep               (char* c);
        void  initializeVariables();
        bool  initializeListener ();
	void  processRequests    ();

	void  setGame            (Game* game         )  { mGame = game; }
	Game* getGame            (                   )  { return mGame; }

protected:
	//Game
	Game*       mGame;

	//Communications
        short unsigned int mPort;

	//Communications
        struct sockaddr_in si_me; //my (server) socket 
        struct sockaddr_in si_other; //other (client) socket

        int s;
        int i;
        int slen;
        char buf[BUFLEN];


};

#endif



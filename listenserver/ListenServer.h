/*
-----------------------------------------------------------------------------
Filename:    ListenServer.h
*/
#ifndef __LISTENSERVER_h_
#define __LISTENSERVER_h_

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

#define MAXBUFLEN 100;

class Game;

class ListenServer
{



public:
    ListenServer(Game* game, char* port);
    virtual ~ListenServer(void);

        void  *get_in_addr       (struct sockaddr *sa);
        void  initializeVariables();
        bool  initializeListener ();
	void  processRequests    ();

	void  setGame            (Game* game         )  { mGame = game; }
	Game* getGame            (                   )  { return mGame; }

protected:
	//Game
	Game*       mGame;

	//Communications
        int         sockfd;
        struct      addrinfo hints, *servinfo, *p;
        int         rv;
        int         numbytes;
        struct      sockaddr_storage their_addr;
        socklen_t   addr_len;
        char        s[INET6_ADDRSTRLEN];
        char* mPort;
        int         mMaxBufferLength;

};

#endif



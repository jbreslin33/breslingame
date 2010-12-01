/*
-----------------------------------------------------------------------------
Filename:    ListenServer.cpp
*/

#include "ListenServer.h"
#include "../Game.h"

#include "../messagehandler/MessageHandler.h"

#include <iostream>

//-------------------------------------------------------------------------------------
ListenServer::ListenServer(Game* game, short unsigned int port)
{
	std::cout << "ListenServer Constructor\n";

	//Game	
	mGame = game;	

        int slen=sizeof(si_other);
	//Communications
    	
   	mPort = port;
    	initializeVariables();
    	initializeListener();
}
//-------------------------------------------------------------------------------------
ListenServer::~ListenServer(void)
{
}

void ListenServer::diep(char *s)
{
        perror(s);
        exit(1);
}


void ListenServer::initializeVariables()
{

}

bool ListenServer::initializeListener()
{
        // i assume i am opening up a socket here? 
        if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        {
                diep("socket");
        }

        //defining structure port etc....?
        memset((char *) &si_me, 0, sizeof(si_me));
        si_me.sin_family = AF_INET;
        si_me.sin_port = htons((short unsigned int)mPort);
        si_me.sin_addr.s_addr = htonl(INADDR_ANY);


        //binding port?
        if (bind(s,(struct sockaddr*) &si_me, sizeof(si_me))==-1)
        {
            diep("bind");
        }


}

void ListenServer::processRequests()
{

	if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&si_other, (socklen_t *)&slen) == -1)
        {
        	diep("recvfrom()");
        }
        printf("Received packet from %s:%d\nData: %s\n\n",
        inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buf);


	printf("listener: packet contains \"%s\"\n", buf);

    	if (mGame->getMessageHandler() != NULL)
    	{
        	printf("We have a MessageHandler\n");
		//sending ip and port info from client....
		mGame->getMessageHandler()->translateMessage( buf, inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port) );
 	}
    	else
    	{
        	printf("No MessageHandler, do nothing\n");
    	}
}

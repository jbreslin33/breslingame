/*
-----------------------------------------------------------------------------
Filename:    Communication.cpp
*/

#include "Communication.h"
#include "../Game.h"

#include "../messagehandler/MessageHandler.h"

#include <iostream>

//-------------------------------------------------------------------------------------
Communication::Communication(Game* game, short unsigned int port)
{
	std::cout << "Communication Constructor\n";

	//Game	
	mGame = game;	

	//Communications
        slen = sizeof(si_other);
   	mPort = port;
    	
	initializeVariables();
    	initializeListener();
}
//-------------------------------------------------------------------------------------
Communication::~Communication(void)
{
}

void Communication::diep(char *s)
{
        perror(s);
        exit(1);
}

void Communication::send(Connection* conn, std::vector<std::string> message)
{

}

void Communication::initializeVariables()
{

}

bool Communication::initializeListener()
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

void Communication::processRequests()
{

	if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&si_other, (socklen_t *)&slen) == -1)
        {
        	diep("recvfrom()");
        }
        printf("Received packet from %s:%d\nData: %s\n\n",
        inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buf);


	printf("listener: packet contains \"%s\"\n", buf);

    	if (mGame->getCommunication() != NULL)
    	{
        //	printf("We have a MessageHandler\n");
		//sending ip and port info from client....
		//mGame->getMessageHandler()->translateMessage( buf, inet_ntoa(si_other.sin_addr)) );
 	}
    	else
    	{
        	printf("No MessageHandler, do nothing\n");
    	}
}

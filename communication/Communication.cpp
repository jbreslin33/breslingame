/*
-----------------------------------------------------------------------------
Filename:    Communication.cpp
*/

#include "Communication.h"
#include "../Game.h"

#include "../connection/Connection.h"

#include <iostream>

//-------------------------------------------------------------------------------------
Communication::Communication(Game* game, const char* port)
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

void Communication::send(Connection* conn, char* p1, char* p2)
{

	printf("parsing message p1:%s\n",p1);
	printf("parsing message p2:%s\n",p2);
/*
	char* total;
        strcpy (total,"");
        strcat (total,p2);
        puts (total);
        send(conn,total);
*/
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
        si_me.sin_port = htons(atoi(mPort));
        si_me.sin_addr.s_addr = htonl(INADDR_ANY);


        //binding port?
        if (bind(s,(struct sockaddr*) &si_me, sizeof(si_me))==-1)
        {
            diep("bind");
        }


}

void Communication::processRequests()
{
	printf("waiting at recvfrom on port:%s",mPort);

	if (recvfrom(s, buf, MAXBUF, 0, (struct sockaddr *)&si_other, (socklen_t *)&slen) == -1)
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

int Communication::send (Connection* conn, char* newMessageToServer )
{
        if (strlen(newMessageToServer) > MAXBUF)
        {
                perror("message too big!");
        }

        int sockfd;
        struct addrinfo hints, *servinfo, *p;
        int rv;
        int numbytes;

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;

	const char* thePort = "38387";

        if ((rv = getaddrinfo(conn->getIP(), thePort, &hints, &servinfo)) != 0) {
                fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
                return 1;
        }

        // loop through all the results and make a socket
        for(p = servinfo; p != NULL; p = p->ai_next) {
                if ((sockfd = socket(p->ai_family, p->ai_socktype,
                                p->ai_protocol)) == -1) {
                        perror("talker: socket");
                        continue;
                }

                break;
        }

        if (p == NULL) {
                fprintf(stderr, "talker: failed to bind socket\n");
                return 2;
        }

        if ((numbytes = sendto(sockfd, newMessageToServer, strlen(newMessageToServer), 0,
                         p->ai_addr, p->ai_addrlen)) == -1) {
                perror("talker: sendto");
                exit(1);
        }

        freeaddrinfo(servinfo);

        printf("talker: sent %d bytes to %s\n", numbytes, conn->getIP());
        close(sockfd);

        return 0;
}


/*
-----------------------------------------------------------------------------
Filename:    ListenServer.cpp
*/

#include "ListenServer.h"
#include "../Game.h"

#include "../messagehandler/MessageHandler.h"



#include <iostream>

//-------------------------------------------------------------------------------------
ListenServer::ListenServer(Game* game, char* port)
{
	std::cout << "ListenServer Constructor\n";

	//Game	
	mGame = game;	

	//Communications
    	mMaxBufferLength = MAXBUFLEN;
   	mPort = port;
    	initializeVariables();
    	initializeListener();
}
//-------------------------------------------------------------------------------------
ListenServer::~ListenServer(void)
{
}

void *ListenServer::get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void ListenServer::initializeVariables()
{

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
}

bool ListenServer::initializeListener()
{
    if ((rv = getaddrinfo(NULL, mPort, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("listener: socket");
            continue;
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("listener: bind");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "listener: failed to bind socket\n");
        return 2;
    }

    freeaddrinfo(servinfo);

    printf("listener: waiting to recvfrom...\n");
}

void ListenServer::processRequests()
{
    //Did something go wrong?
    addr_len = sizeof their_addr;

    char newClientMessage[mMaxBufferLength];

    for (int i = 0; i < mMaxBufferLength; i++)
    newClientMessage[i] = NULL;



    if ((numbytes = recvfrom(sockfd, newClientMessage, mMaxBufferLength-1 , 0,
        (struct sockaddr *)&their_addr, &addr_len)) == -1) {
        perror("recvfrom");
        exit(1);
    }
    //printf("ipclient:%s",their_addr);


char ip4[INET_ADDRSTRLEN];  // space to hold the IPv4 string
//struct sockaddr_in sa;      // pretend this is loaded with something

inet_ntop(AF_INET, &(*their_addr.sin_addr), ip4, INET_ADDRSTRLEN);

printf("The IPv4 address is: %s\n", ip4);



    printf("listener: packet contains \"%s\"\n", newClientMessage);

    if (mGame->getMessageHandler() != NULL)
    {
        printf("We have a MessageHandler\n");
	mGame->getMessageHandler()->translateMessage(newClientMessage);
	
    }
    else
    {
        printf("No MessageHandler, do nothing\n");
    }
}

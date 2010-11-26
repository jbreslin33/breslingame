
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

#include "Talker.h"
#include "../Game.h"


Talker::Talker(Game* game)
{
	mGame = game;
}

Talker::~Talker(void)
{
}


void Talker::translateMessage(std::string p1)
{
        sendMessageToServer(p1);
}

void Talker::translateMessage(std::string p1, std::string p2)
{
        p1.append(p2);
        sendMessageToServer(p1);
}

void Talker::translateMessage(std::string p1, std::string p2, std::string p3)
{
        p1.append(p2);
        p1.append(p3);
        sendMessageToServer(p1);
}


void Talker::translateMessage(std::string p1, std::string p2, std::string p3, std::string p4)
{
        p1.append(p2);
        p1.append(p3);
        p1.append(p4);
        sendMessageToServer(p1);
}

	
int Talker::sendMessageToServer (char* newMessageToServer )
{
	if (strlen(newMessageToServer) > 100)
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

	if ((rv = getaddrinfo(mGame->getServerIP(), SERVERPORT, &hints, &servinfo)) != 0) {
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

	printf("talker: sent %d bytes to %s\n", numbytes, mGame->getServerIP());
	close(sockfd);

	return 0;

}


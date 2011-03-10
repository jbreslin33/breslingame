#ifndef SERVERSIDENETWORKEDCLIENT_H
#define SERVERSIDENETWORKEDCLIENT_H

#define COMMAND_HISTORY_SIZE		64

#include "../client/client.h"

#include "../math/Vector3D.h"
#include "../command/serverSideCommand.h"

#include "../tdreamsock/dreamSock.h"

class ServerSideNetworkedClient : public Client
{

public:

ServerSideNetworkedClient();
~ServerSideNetworkedClient();

	ServerSideCommand frame[COMMAND_HISTORY_SIZE];
	ServerSideCommand serverFrame;
	ServerSideCommand command;

	long processedFrame;

	struct sockaddr address;
	dreamClient *netClient;

	Vector3D startPos;
	bool team;

	ServerSideNetworkedClient *next;
};
#endif

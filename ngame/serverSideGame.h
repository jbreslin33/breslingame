#ifndef SERVER_H
#define SERVER_H

#include <string.h>

#include "../tdreamsock/dreamSock.h"

#define COMMAND_HISTORY_SIZE		64

#define KEY_UP						1
#define KEY_DOWN					2
#define KEY_LEFT					4
#define KEY_RIGHT					8

#define CMD_KEY						1
#define CMD_ORIGIN					4

#define USER_MES_FRAME				1
#define USER_MES_NONDELTAFRAME		2
#define USER_MES_SERVEREXIT			3


class ServerSideGame
{
public:

	ServerSideGame();
	~ServerSideGame();

	virtual void ReadPackets() { bool donothing; }

};

#endif

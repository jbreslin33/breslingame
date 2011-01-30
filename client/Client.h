#ifndef CLIENT_H
#define CLIENT_H

#define COMMAND_HISTORY_SIZE		64 //this should go somewher else....

//#include "../command/Command.h"
#include "../math/Vector3D.h"

class Command;
//class Vector2D;

class Client
{

public:

Client();
~Client();


	Vector3D startPos;

	int index;

	char nickname[30];

	bool team;


//	Client*   next;
};
#endif

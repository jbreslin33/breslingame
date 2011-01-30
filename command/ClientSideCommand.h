#ifndef CLIENTSIDECOMMAND_H
#define CLIENTSIDECOMMAND_H

#include "Command.h"

#include "../math/Vector3D.h"

class ClientSideCommand : public Command
{
public:
ClientSideCommand();
~ClientSideCommand();
	
	Vector3D predictedOrigin;
};
#endif

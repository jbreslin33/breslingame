#ifndef COMMAND_H
#define COMMAND_H

#include "../math/Vector3D.h"

class Command
{
public:
Command();
~Command();
	
	int      key;
	int      msec;
	Vector3D vel;
	Vector3D origin;

};
#endif

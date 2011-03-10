/******************************************/
/* MMOG programmer's guide                */
/* Tutorial game server                   */
/* Programming:						      */
/* Teijo Hakala						      */
/******************************************/
#include "serverSideGame.h"

ServerSideGame::ServerSideGame()
{
	clientList	= NULL;
	clients		= 0;

	realtime	= 0;
	servertime	= 0;

	index		= 0;

	framenum	= 0;
}

ServerSideGame::~ServerSideGame()
{

}


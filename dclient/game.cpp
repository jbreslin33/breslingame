#include "game.h"
#include "../shape/clientSideShape.h"
//#ifdef WIN32
#include "../tdreamsock/dreamSockLog.h"
//#endif

Game::Game()
{

	clientList		= NULL;
	localClient		= NULL;
	clients			= 0;

	memset(&inputClient, 0, sizeof(clientData));

	frametime		= 0.0f;

	rendertime		= 0.0f;

	init			= false;

	gameIndex		= 0;

	next			= NULL;
	keepRunning = true;
}
Game::~Game()
{
}

void Game::AddClient(int local, int ind, char *name)
{
	// First get a pointer to the beginning of client list
	clientData *list = clientList;
	clientData *prev;

	LogString("App: Client: Adding client with index %d", ind);

	// No clients yet, adding the first one
	if(clientList == NULL)
	{
		LogString("App: Client: Adding first client");

		clientList = (clientData *) calloc(1, sizeof(clientData));

		if(local)
		{
			LogString("App: Client: This one is local");
			localClient = clientList;
		}

		clientList->index = ind;
LogString("before");
		strcpy(clientList->nickname, name);
LogString("after");
		createPlayer(ind);

		clientList->next = NULL;
	}
	else
	{
		LogString("App: Client: Adding another client");

		prev = list;
		list = clientList->next;

		while(list != NULL)
		{
			prev = list;
			list = list->next;
		}

		list = (clientData *) calloc(1, sizeof(clientData));

		if(local)
		{
			LogString("App: Client: This one is local");
			localClient = list;
		}

		list->index = ind;
LogString("before strcpy");
		strcpy(list->nickname, name);
LogString("after strcpy");
		clientList->next = NULL;

		list->next = NULL;
		prev->next = list;

		createPlayer(ind);
	}

	clients++;
/*
	// If we just joined the game, request a non-delta compressed frame
	if(local)
		SendRequestNonDeltaFrame();
*/
}

clientData *Game::GetClientPointer(int index)
{
	for(clientData *clList = clientList; clList != NULL; clList = clList->next)
	{
		if(clList->index == index)
			return clList;
	}

	return NULL;
}

//Player stuff
void Game::createPlayer(int index)
{
	LogString("begin createPlayer");
        //create a human player and or ghost player 
        ClientSideShape* jay = new ClientSideShape(mSceneMgr,"jay" + index,0,0,0,"sinbad.mesh");
        //mClientSideShapeVector.push_back(jay);
	LogString("created Player");
        clientData *client = GetClientPointer(index);
        client->mClientSideShape = jay;
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc:
//-----------------------------------------------------------------------------
void Game::RemoveClients(void)
{
	clientData *list = clientList;
	clientData *next;

	while(list != NULL)
	{
		if(list)
		{
			next = list->next;
			free(list);
		}

		list = next;
	}

	clientList = NULL;
	clients = 0;
}

void Game::RemoveClient(int ind)
{
	clientData *list = clientList;
	clientData *prev = NULL;
	clientData *next = NULL;

	// Look for correct client and update list
	for( ; list != NULL; list = list->next)
	{
		if(list->index == ind)
		{
			if(prev != NULL)
			{
				prev->next = list->next;
			}

			break;
		}

		prev = list;
	}

	// First entry
	if(list == clientList)
	{
		if(list)
		{
			next = list->next;
			free(list);
		}

		list = NULL;
		clientList = next;
	}

	// Other
	else
	{
		if(list)
		{
			next = list->next;
			free(list);
		}

		list = next;
	}

	clients--;

}


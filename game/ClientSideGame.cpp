//#include "Tutorial4.h"
//#include "baseGame.h"
//#include "network.h"
#include "../game/ClientSideGame.h"
#include "../dreamsock/DreamClient.h"
#include "../network/clientSideNetwork.h"
#include "../basegame/baseGame.h"

ClientSideGame::ClientSideGame(BaseGame* baseGame)
{

	mBaseGame = baseGame;
        networkClient   = new DreamClient;
        clientList              = NULL;
        localClient             = NULL;
        clients                 = 0;

        memset(&inputClient, 0, sizeof(ClientSideClient));

        frametime               = 0.0f;

        init                    = false;

        gameIndex               = 0;

        next                    = NULL;

/************/
/*
	mBaseGame = baseGame;


	mClientSideNetwork = new ClientSideNetwork(this);

	mClientSideNetwork->StartConnection();

	
	clientList		= NULL;
	localClient		= NULL;
	clients			= 0;

	memset(&inputClient, 0, sizeof(ClientSideClient));

	frametime		= 0.0f;

	init			= false;

	gameIndex		= 0;

	next			= NULL;
*/
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
ClientSideGame::~ClientSideGame()
{
	delete networkClient;
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideGame::Shutdown(void)
{
	mClientSideNetwork->Disconnect();
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
ClientSideClient *ClientSideGame::GetClientPointer(int index)
{
	for(ClientSideClient *clList = clientList; clList != NULL; clList = clList->next)
	{
		if(clList->index == index)
			return clList;
	}

	return NULL;
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideGame::CheckKeys(void)
{
	inputClient.command.key = 0;

	if(mBaseGame->keys[VK_ESCAPE])
	{
		Shutdown();

		mBaseGame->keys[VK_ESCAPE] = false;
	}

	if(mBaseGame->keys[VK_DOWN])
	{
		inputClient.command.key |= KEY_DOWN;
	}

	if(mBaseGame->keys[VK_UP])
	{
		inputClient.command.key |= KEY_UP;
	}

	if(mBaseGame->keys[VK_LEFT])
	{
		inputClient.command.key |= KEY_LEFT;
	}

	if(mBaseGame->keys[VK_RIGHT])
	{
		inputClient.command.key |= KEY_RIGHT;
	}

	inputClient.command.msec = (int) (frametime * 1000);
	
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideGame::CheckPredictionError(int a)
{
	if(a < 0 && a > COMMAND_HISTORY_SIZE)
		return;

	float errorX =
		localClient->serverFrame.origin.x - localClient->frame[a].predictedOrigin.x;
		
	float errorY =
		localClient->serverFrame.origin.y - localClient->frame[a].predictedOrigin.y;

	// Fix the prediction error
	if( (errorX != 0.0f) || (errorY != 0.0f) )
	{
		localClient->frame[a].predictedOrigin.x = localClient->serverFrame.origin.x;
		localClient->frame[a].predictedOrigin.y = localClient->serverFrame.origin.y;

		localClient->frame[a].vel.x = localClient->serverFrame.vel.x;
		localClient->frame[a].vel.y = localClient->serverFrame.vel.y;

		LogString("Prediction error for frame %d:     %f, %f\n", a,
			errorX, errorY);
	}
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideGame::CalculateVelocity(ClientSideCommand *command, float frametime)
{
	float multiplier = 100.0f;

	command->vel.x = 0.0f;
	command->vel.y = 0.0f;

	if(command->key & KEY_UP)
	{
		command->vel.y += multiplier * frametime;
	}

	if(command->key & KEY_DOWN)
	{
		command->vel.y += -multiplier * frametime;
	}

	if(command->key & KEY_LEFT)
	{
		command->vel.x += -multiplier * frametime;
	}

	if(command->key & KEY_RIGHT)
	{
		command->vel.x += multiplier * frametime;
	}
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideGame::PredictMovement(int prevFrame, int curFrame)
{
	if(!localClient)
		return;

	float frametime = inputClient.frame[curFrame].msec / 1000.0f;

	localClient->frame[curFrame].key = inputClient.frame[curFrame].key;

	//
	// Player ->
	//
	
	// Process commands
	CalculateVelocity(&localClient->frame[curFrame], frametime);

	// Calculate new predicted origin
	localClient->frame[curFrame].predictedOrigin.x =
		localClient->frame[prevFrame].predictedOrigin.x + localClient->frame[curFrame].vel.x;

	localClient->frame[curFrame].predictedOrigin.y =
		localClient->frame[prevFrame].predictedOrigin.y + localClient->frame[curFrame].vel.y;

	// Copy values to "current" values
	localClient->command.predictedOrigin.x	= localClient->frame[curFrame].predictedOrigin.x;
	localClient->command.predictedOrigin.y	= localClient->frame[curFrame].predictedOrigin.y;
	localClient->command.vel.x				= localClient->frame[curFrame].vel.x;
	localClient->command.vel.y				= localClient->frame[curFrame].vel.y;
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideGame::MoveObjects(void)
{
	if(!localClient)
		return;

	ClientSideClient *client = clientList;

	Ogre::Vector3 transVector = Ogre::Vector3::ZERO;

	for( ; client != NULL; client = client->next)
	{
		// Remote players
		if(client != localClient)
		{
			CalculateVelocity(&client->command, frametime);

			client->command.origin.x += client->command.vel.x;
			client->command.origin.y += client->command.vel.y;

            transVector.x = client->command.origin.x;
            transVector.y = client->command.origin.y;

			client->myNode->setPosition(transVector);


		}

		//Local player
		else
		{
			client->command.origin.x = client->command.predictedOrigin.x;
			client->command.origin.y = client->command.predictedOrigin.y;

			transVector.x = client->command.origin.x;
            transVector.y = client->command.origin.y;

			client->myNode->setPosition(transVector);


		}
	}
}


//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideGame::AddClient(int local, int ind, char *name)
{
	// First get a pointer to the beginning of client list
	ClientSideClient *list = clientList;
	ClientSideClient *prev;

	LogString("App: Client: Adding client with index %d", ind);

	// No clients yet, adding the first one
	if(clientList == NULL)
	{
		LogString("App: Client: Adding first client");

		clientList = (ClientSideClient *) calloc(1, sizeof(ClientSideClient));

		if(local)
		{
			LogString("App: Client: This one is local");
			localClient = clientList;
		}

		clientList->index = ind;
		strcpy(clientList->nickname, name);

		if(clients % 2 == 0) 
			mBaseGame->createPlayer(ind);
		else
			mBaseGame->createPlayer(ind);

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

		list = (ClientSideClient *) calloc(1, sizeof(ClientSideClient));

		if(local)
		{
			LogString("App: Client: This one is local");
			localClient = list;
		}

		list->index = ind;
		strcpy(list->nickname, name);

		clientList->next = NULL;

		list->next = NULL;
		prev->next = list;

		if(clients % 2 == 0) 
			mBaseGame->createPlayer(ind);
		else
			mBaseGame->createPlayer(ind);

		
	}

	clients++;

	// If we just joined the game, request a non-delta compressed frame
	if(local)
		mClientSideNetwork->SendRequestNonDeltaFrame();

}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideGame::RemoveClient(int ind)
{
	ClientSideClient *list = clientList;
	ClientSideClient *prev = NULL;
	ClientSideClient *next = NULL;

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

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void ClientSideGame::RemoveClients(void)
{
	ClientSideClient *list = clientList;
	ClientSideClient *next;

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

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


void Game::MovePlayer(void)
{

	static Ogre::Real mMove = 17.0;
	Ogre::Vector3 transVector = Ogre::Vector3::ZERO;


	if(keys[VK_DOWN])
	{
		transVector.y -= mMove;

	}

	if(keys[VK_UP])
	{
		transVector.y += mMove;
	}

	if(keys[VK_LEFT])
	{
		transVector.x -= mMove;
	}

	if(keys[VK_RIGHT])
	{
		transVector.x += mMove;
	}

	if(localClient)
	   localClient->mClientSideShape->getSceneNode()->translate(transVector * rendertime, Ogre::Node::TS_LOCAL);

}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc:
//-----------------------------------------------------------------------------
void Game::MoveObjects(void)
{
	if(!localClient)
		return;

	clientData *client = clientList;

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

			client->mClientSideShape->getSceneNode()->setPosition(transVector);


		}

		//Local player
		else
		{
			client->command.origin.x = client->command.predictedOrigin.x;
			client->command.origin.y = client->command.predictedOrigin.y;

			//memcpy(&client->command, &inputClient.command, sizeof(command_t));
			//CalculateVelocity(&inputClient.command, frametime);

			//client->command.origin.x += client->command.vel.x;
			//client->command.origin.y += client->command.vel.y;

            transVector.x = client->command.predictedOrigin.x;
            transVector.y = client->command.predictedOrigin.y;

			//transVector.x = client->command.vel.x;
            //transVector.y = client->command.vel.y;

			//client->myNode->translate(transVector, Ogre::Node::TS_LOCAL);
            client->mClientSideShape->getSceneNode()->setPosition(transVector);

/*
            LogString("transVector.x %f: ", transVector.x);
			LogString("transVector.y %f: ", transVector.y);
			LogString("predictedOrigin.x %f: ", client->command.predictedOrigin.x);
			LogString("predictedOrigin.y %f: ", client->command.predictedOrigin.y);
*/
		}
	}
}


void Game::CalculateVelocity(command_t *command, float frametime)
{
	float multiplier = 17.0f;

	command->vel.x = 0.0f;
	command->vel.y = 0.0f;
	//localClient->command.vel.x = 0.0f;
	//localClient->command.vel.y = 0.0f;


	if(command->key & KEY_UP)
	{
		command->vel.y += multiplier * frametime;
		//localClient->command.vel.y += multiplier * frametime;
	}

	if(command->key & KEY_DOWN)
	{
		command->vel.y += -multiplier * frametime;
		//localClient->command.vel.y += -multiplier * frametime;
	}

	if(command->key & KEY_LEFT)
	{
		command->vel.x += -multiplier * frametime;
		//localClient->command.vel.x += -multiplier * frametime;
	}

	if(command->key & KEY_RIGHT)
	{
		command->vel.x += multiplier * frametime;
		//localClient->command.vel.x += multiplier * frametime;
	}
}



bool Game::CheckKeys(void)
{
	inputClient.command.key = 0;

	if(keys[VK_ESCAPE])
	{
		return false;
		Shutdown();

		keys[VK_ESCAPE] = false;
	}

	if(keys[VK_DOWN])
	{
		inputClient.command.key |= KEY_DOWN;
	}

	if(keys[VK_UP])
	{
		inputClient.command.key |= KEY_UP;
	}

	if(keys[VK_LEFT])
	{
		inputClient.command.key |= KEY_LEFT;
	}

	if(keys[VK_RIGHT])
	{
		inputClient.command.key |= KEY_RIGHT;
	}

	inputClient.command.msec = (int) (frametime * 1000);
	return true;
}

bool Game::processUnbufferedInput(const Ogre::FrameEvent& evt)
{

    if (mKeyboard->isKeyDown(OIS::KC_I)) // Forward
    {
		keys[VK_UP] = TRUE;
    }
	else
	{
        keys[VK_UP] = FALSE;
	}
    if (mKeyboard->isKeyDown(OIS::KC_K)) // Backward
    {
		keys[VK_DOWN] = TRUE;
    }
	else
	{
        keys[VK_DOWN] = FALSE;
	}

    if (mKeyboard->isKeyDown(OIS::KC_J)) // Left - yaw or strafe
    {
		keys[VK_LEFT] = TRUE;
    }
	else
	{
        keys[VK_LEFT] = FALSE;
	}
    if (mKeyboard->isKeyDown(OIS::KC_L)) // Right - yaw or strafe
    {
		keys[VK_RIGHT] = TRUE;
    }
	else
	{
        keys[VK_RIGHT] = FALSE;
	}

    return true;
}

void Game::Shutdown(void)
{
	//Disconnect();
}


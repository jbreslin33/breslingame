#include "polyNetworkedGame.h"
#include "../shape/clientSideShape.h"

bool keys[256];

PolyNetworkedGame::PolyNetworkedGame()
{

}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc:
//-----------------------------------------------------------------------------
PolyNetworkedGame::~PolyNetworkedGame()
{
	delete networkClient;
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc:
//-----------------------------------------------------------------------------
void PolyNetworkedGame::Shutdown(void)
{
	Disconnect();
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc:
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Name: empty()
// Desc:
//-----------------------------------------------------------------------------
bool PolyNetworkedGame::CheckKeys(void)
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

//-----------------------------------------------------------------------------
// Name: empty()
// Desc:
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Name: empty()
// Desc:
//-----------------------------------------------------------------------------
void PolyNetworkedGame::CalculateVelocity(command_t *command, float frametime)
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

//-----------------------------------------------------------------------------
// Name: empty()
// Desc:
//-----------------------------------------------------------------------------
void PolyNetworkedGame::PredictMovement(int prevFrame, int curFrame)
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
	localClient->command.vel.y
		= localClient->frame[curFrame].vel.y;
}

void PolyNetworkedGame::MovePlayer(void)
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
void PolyNetworkedGame::MoveObjects(void)
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

//-------------------------------------------------------------------------------------
void PolyNetworkedGame::createScene(void)
{
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));

    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(250, 150, 250));
    pointLight->setDiffuseColour(Ogre::ColourValue::White);
    pointLight->setSpecularColour(Ogre::ColourValue::White);
	        Ogre::Light* light = mSceneMgr->getLight("pointLight");
        light->setVisible(true);
}
//-------------------------------------------------------------------------------------
bool PolyNetworkedGame::processUnbufferedInput(const Ogre::FrameEvent& evt)
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
//-------------------------------------------------------------------------------------
bool PolyNetworkedGame::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    bool ret = BaseApplication::frameRenderingQueued(evt);

    if(!processUnbufferedInput(evt)) return false;


	//if(game != NULL)
	//{


		rendertime = evt.timeSinceLastFrame;

		//game->Frame();
	//}

    return ret;
}
//-------------------------------------------------------------------------------------
 void PolyNetworkedGame::go(void)
{
#ifdef _DEBUG
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif

    if (!setup())
        return;

	while(keepRunning) {
		CheckKeys();

		RunNetwork(rendertime * 1000);
Ogre::WindowEventUtilities::messagePump();
		keepRunning = mRoot->renderOneFrame();
	}
    //mRoot->startRendering();

    // clean up
    destroyScene();
}



//**************************************************************
//BEGIN NETWORK CODE FUNCTIONS
//************************************************
void PolyNetworkedGame::StartConnection(char* serverIP)
{
//	LogString("StartConnection");

	//gameIndex = ind;

	int ret = networkClient->Initialise("", serverIP, 30004);

	if(ret == DREAMSOCK_CLIENT_ERROR)
	{
		char text[64];
		sprintf(text, "Could not open client socket");

		//MessageBox(NULL, text, "Error", MB_OK);
	}

	Connect();
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc:
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Name: empty()
// Desc:
//-----------------------------------------------------------------------------
void PolyNetworkedGame::AddClient(int local, int ind, char *name)
{
	Game::AddClient(local,ind,name);
	/*
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
		strcpy(clientList->nickname, name);

		if(clients % 2 == 0)
			createPlayer(ind);
		else
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
		strcpy(list->nickname, name);

		clientList->next = NULL;

		list->next = NULL;
		prev->next = list;

		if(clients % 2 == 0)
			createPlayer(ind);
		else
			createPlayer(ind);


	}

	clients++;
*/
	// If we just joined the game, request a non-delta compressed frame
	if(local)
		SendRequestNonDeltaFrame();

}

void PolyNetworkedGame::RunNetwork(int msec)
{
    //MovePlayer();

	static int time = 0;
	time += msec;

	// Framerate is too high
	if(time < (1000 / 60)) {
        MovePlayer();
		return;
	}

	frametime = time / 1000.0f;
	time = 0;

	// Read packets from server, and send new commands
	ReadPackets();
	SendCommand();

	int ack = networkClient->GetIncomingAcknowledged();
	int current = networkClient->GetOutgoingSequence();

	// Check that we haven't gone too far
	if(current - ack > COMMAND_HISTORY_SIZE)
		return;

	// Predict the frames that we are waiting from the server
	for(int a = ack + 1; a < current; a++)
	{
		int prevframe = (a-1) & (COMMAND_HISTORY_SIZE-1);
		int frame = a & (COMMAND_HISTORY_SIZE-1);

		PredictMovement(prevframe, frame);
	}

	MoveObjects();


}

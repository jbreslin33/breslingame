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


//-----------------------------------------------------------------------------
// Name: empty()
// Desc:
//-----------------------------------------------------------------------------



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

void PolyNetworkedGame::Shutdown(void)
{
	Disconnect();
}

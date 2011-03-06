#include "polyNetworkedGame.h"
#include "../shape/clientSideShape.h"

bool keys[256];

PolyNetworkedGame::PolyNetworkedGame()
{
}

PolyNetworkedGame::~PolyNetworkedGame()
{

}

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

	while(keepRunning)
	{
		gameLoop();
	}

    // clean up
    destroyScene();
}

void PolyNetworkedGame::gameLoop()
{
	CheckKeys();
	RunNetwork(rendertime * 1000);
	Ogre::WindowEventUtilities::messagePump();
	keepRunning = mRoot->renderOneFrame();
}

void PolyNetworkedGame::StartConnection(char* serverIP)
{
	int ret = networkClient->Initialise("", serverIP, 30004);

	if(ret == DREAMSOCK_CLIENT_ERROR)
	{
		char text[64];
		sprintf(text, "Could not open client socket");
	}

	Connect();
}

void PolyNetworkedGame::AddClient(int local, int ind, char *name)
{
	Game::AddClient(local,ind,name);

	// If we just joined the game, request a non-delta compressed frame
	if(local)
		SendRequestNonDeltaFrame();

}

void PolyNetworkedGame::RunNetwork(int msec)
{
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

//iam going to put the following in Game.cpp's game loop...

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



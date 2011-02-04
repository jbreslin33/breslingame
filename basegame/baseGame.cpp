#include "baseGame.h"

#include "../baseapplication/BaseApplication.h"

#include "../dreamsock/DreamClient.h"
#include "../dreamsock/DreamSock.h"

#include "../client/ClientSideClient.h"

BaseGame*          mBaseGame;
ClientSideNetwork* mClientSideNetwork;

bool keys[256];

BaseGame::BaseGame()
{
	networkClient	= new DreamClient();

	clientList		= NULL;
	localClient		= NULL;

	memset(&inputClient, 0, sizeof(ClientSideClient));

	frametime		= 0.0f;

	init			= false;

	next			= NULL;
}

BaseGame::~BaseGame()
{
	delete networkClient;
}

void BaseGame::Shutdown(void)
{
	Disconnect();
}

ClientSideClient *BaseGame::GetClientPointer(int index)
{
	for(ClientSideClient *clList = clientList; clList != NULL; clList = clList->next)
	{
		if(clList->index == index)
			return clList;
	}

	return NULL;
}

void BaseGame::CheckKeys(void)
{
	inputClient.command.key = 0;

	if(keys[VK_ESCAPE])
	{
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
	
}

void BaseGame::CheckPredictionError(int a)
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

void BaseGame::CalculateVelocity(ClientSideCommand *command, float frametime)
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

void BaseGame::PredictMovement(int prevFrame, int curFrame)
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

void BaseGame::MoveObjects(void)
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


void BaseGame::StartConnection(char serverIP[32])

{
//	LogString("StartConnection");

	//gameIndex = ind;

//char serverIP[32] = "192.168.2.112";
	int ret = networkClient->Initialise("", serverIP, 30004);

	if(ret == DREAMSOCK_CLIENT_ERROR)
	{
		char text[64];
		sprintf(text, "Could not open client socket");

		//MessageBox(NULL, text, "Error", MB_OK);
	}

	Connect();
}

void BaseGame::AddClient(int local, int ind, char *name)
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

			createPlayer(ind);
	}

	// If we just joined the game, request a non-delta compressed frame
	if(local)
		SendRequestNonDeltaFrame();

}

void BaseGame::RemoveClient(int ind)
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
}

void BaseGame::RemoveClients(void)
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
}

void BaseGame::SendRequestNonDeltaFrame(void)
{
	char data[1400];
	DreamMessage message;
	message.Init(data, sizeof(data));

	message.WriteByte(USER_MES_NONDELTAFRAME);
	message.AddSequences(networkClient);

	networkClient->SendPacket(&message);
}

void BaseGame::Connect(void)
{
	if(init)
	{
		LogString("ArmyWar already initialised");
		return;
	}

	LogString("BaseGame::Connect");

	init = true;

	networkClient->SendConnect("myname");
}

void BaseGame::Disconnect(void)
{
	if(!init)
		return;

	LogString("BaseGame::Disconnect");

	init = false;
	localClient = NULL;
	memset(&inputClient, 0, sizeof(ClientSideClient));

	networkClient->SendDisconnect();
}

void BaseGame::ReadMoveCommand(DreamMessage *mes, ClientSideClient *client)
{
	// Key
	client->serverFrame.key				= mes->ReadByte();

	// Heading
	//client->serverFrame.heading			= mes->ReadShort();

	// Origin
	client->serverFrame.origin.x		= mes->ReadFloat();
	client->serverFrame.origin.y		= mes->ReadFloat();
	client->serverFrame.vel.x			= mes->ReadFloat();
	client->serverFrame.vel.y			= mes->ReadFloat();

	// Read time to run command
	client->serverFrame.msec = mes->ReadByte();

	memcpy(&client->command, &client->serverFrame, sizeof(ClientSideCommand));

	// Fill the history array with the position we got
	for(int f = 0; f < COMMAND_HISTORY_SIZE; f++)
	{
		client->frame[f].predictedOrigin.x = client->command.origin.x;
		client->frame[f].predictedOrigin.y = client->command.origin.y;
	}
}

void BaseGame::ReadDeltaMoveCommand(DreamMessage *mes, ClientSideClient *client)
{
	int processedFrame;
	int flags = 0;

	// Flags
	flags = mes->ReadByte();

	// Key
	if(flags & CMD_KEY)
	{
		client->serverFrame.key = mes->ReadByte();

		client->command.key = client->serverFrame.key;
		LogString("Client %d: Read key %d", client->index, client->command.key);
	}

	if(flags & CMD_ORIGIN)
	{
		processedFrame = mes->ReadByte();
	}

	// Origin
	if(flags & CMD_ORIGIN)
	{
		client->serverFrame.origin.x = mes->ReadFloat();
		client->serverFrame.origin.y = mes->ReadFloat();

		client->serverFrame.vel.x = mes->ReadFloat();
		client->serverFrame.vel.y = mes->ReadFloat();

		if(client == localClient)
		{
			CheckPredictionError(processedFrame);
		}

		else
		{
			client->command.origin.x = client->serverFrame.origin.x;
			client->command.origin.y = client->serverFrame.origin.y;

			client->command.vel.x = client->serverFrame.vel.x;
			client->command.vel.y = client->serverFrame.vel.y;
		}
	}

	// Read time to run command
	client->command.msec = mes->ReadByte();
}

void BaseGame::BuildDeltaMoveCommand(DreamMessage *mes, ClientSideClient *theClient)
{
	int flags = 0;
	int last = (networkClient->GetOutgoingSequence() - 1) & (COMMAND_HISTORY_SIZE-1);

	// Check what needs to be updated
	if(theClient->frame[last].key != theClient->command.key)
		flags |= CMD_KEY;

	// Add to the message
	// Flags
	mes->WriteByte(flags);

	// Key
	if(flags & CMD_KEY)
	{
		mes->WriteByte(theClient->command.key);
	}

	mes->WriteByte(theClient->command.msec);
}

void BaseGame::RunNetwork(int msec)
{
	static int time = 0;
	time += msec;

	// Framerate is too high
	if(time < (1000 / 60))
		return;

	frametime = time / 1000.0f;
	time = 0;

	// Read packets from server, and send new commands
	mClientSideNetwork->ReadPackets();
	mClientSideNetwork->SendCommand();

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

void BaseGame::createPlayer(int index)
{
	Ogre::Entity* NinjaEntity = mSceneMgr->createEntity("ninja.mesh");
	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    	node->attachObject(NinjaEntity);
	ClientSideClient *client = mBaseGame->GetClientPointer(index);
	client->myNode = node;
}

void BaseGame::createScene(void)
{
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));
 
    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(250, 150, 250));
    pointLight->setDiffuseColour(Ogre::ColourValue::White);
    pointLight->setSpecularColour(Ogre::ColourValue::White);
}

bool BaseGame::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
 
    	if (mKeyboard->isKeyDown(OIS::KC_I)) // Forward
    	{
		keys[VK_UP] = true;
   	}
	else
	{
        	keys[VK_UP] = false;
	}
    	
	if (mKeyboard->isKeyDown(OIS::KC_K)) // Backward
    	{
		keys[VK_DOWN] = true;
    	}
	else
	{
        	keys[VK_DOWN] = false;
	}

    	if (mKeyboard->isKeyDown(OIS::KC_J)) // Left - yaw or strafe
    	{
		keys[VK_LEFT] = true;
    	}
	else
	{
        	keys[VK_LEFT] = false;
	}
    	
	if (mKeyboard->isKeyDown(OIS::KC_L)) // Right - yaw or strafe
    	{
		keys[VK_RIGHT] = true;
	}
	else
	{
        	keys[VK_RIGHT] = false;
	}
         
    return true;
}

bool BaseGame::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    bool ret = BaseApplication::frameRenderingQueued(evt);
 
    if(!processUnbufferedInput(evt)) return false;

	if(mBaseGame != NULL && mClientSideNetwork != NULL)
	{
		mBaseGame->RunNetwork(evt.timeSinceLastFrame * 1000);
		mBaseGame->CheckKeys();
	}
 
    return ret;
}

bool BaseGame::keyPressed( const OIS::KeyEvent &arg )
{
	BaseApplication::keyPressed(arg);
    	Ogre::LogManager::getSingletonPtr()->logMessage("*** keyPressed BaseGame n***");
	return true;
} 
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif
 
#ifdef __cplusplus
extern "C" {
#endif
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        mBaseGame          = new BaseGame;
	mClientSideNetwork = new ClientSideNetwork(mBaseGame);
	 
	
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	mBaseGame->StartConnection(strCmdLine);
#else
	mBaseGame->StartConnection(argv[1]);
#endif
 
        try {
            mBaseGame->go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }
 
        return 0;
    }
 
#ifdef __cplusplus
}
#endif

//#include "Tutorial4.h"
#include "baseGame.h"
#include "../network/network.h"
#include "../dreamsock/DreamClient.h"

BaseGame* game;
bool keys[256];


BaseGame::BaseGame()
{
	networkClient	= new DreamClient();
	clientList		= NULL;
	localClient		= NULL;
	clients			= 0;

	memset(&inputClient, 0, sizeof(ClientSideClient));

	frametime		= 0.0f;

	init			= false;

	gameIndex		= 0;

	next			= NULL;
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
BaseGame::~BaseGame()
{
	delete networkClient;
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
void BaseGame::Shutdown(void)
{
	Disconnect();
}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
ClientSideClient *BaseGame::GetClientPointer(int index)
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

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
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


void BaseGame::createPlayer(int index)
{
	Ogre::Entity* NinjaEntity = mSceneMgr->createEntity("ninja.mesh");
	//Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(NinjaEntity);
    //node->setPosition(Ogre::Vector3(10, 10, 10));

    ClientSideClient *client = game->GetClientPointer(index);

	client->myNode = node;
}
//-------------------------------------------------------------------------------------
void BaseGame::createScene(void)
{
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));
 
    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(250, 150, 250));
    pointLight->setDiffuseColour(Ogre::ColourValue::White);
    pointLight->setSpecularColour(Ogre::ColourValue::White);
}
//-------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------
bool BaseGame::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    bool ret = BaseApplication::frameRenderingQueued(evt);
 
    if(!processUnbufferedInput(evt)) return false;

	if(game != NULL)
	{
		game->RunNetwork(evt.timeSinceLastFrame * 1000);
		game->CheckKeys();
		//game->Frame();
	}
 
    return ret;
}
//-------------------------------------------------------------------------------------
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
        // Create application object
         game = new BaseGame;

		//game = new BaseGame;
	    game->StartConnection();

 
        try {
            game->go();
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

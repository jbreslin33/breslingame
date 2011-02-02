//#include "Tutorial4.h"
#include "baseGame.h"
#include "../network/network.h"
#include "../dreamsock/DreamClient.h"
#include "../client/ClientSideClient.h"
#include "../game/ClientSideGame.h"
#include "../network/clientSideNetwork.h"

#include "../dreamsock/DreamConsole.h"

BaseGame*          mBaseGame;
ClientSideGame*    mClientSideGame;
ClientSideNetwork* mClientSideNetwork;

BaseGame::BaseGame()
{

}

//-----------------------------------------------------------------------------
// Name: empty()
// Desc: 
//-----------------------------------------------------------------------------
BaseGame::~BaseGame()
{
}


void BaseGame::createPlayer(int index)
{
        Ogre::Entity* NinjaEntity = mSceneMgr->createEntity("ninja.mesh");
        //Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
        Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(NinjaEntity);
    //node->setPosition(Ogre::Vector3(10, 10, 10));

    ClientSideClient *client = mClientSideGame->GetClientPointer(index);

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

	if(mClientSideGame != NULL)
	{
		mClientSideGame->mClientSideNetwork->RunNetwork(evt.timeSinceLastFrame * 1000);
		mClientSideGame->CheckKeys();
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
         mBaseGame 	    = new BaseGame;
	 mClientSideGame    = new ClientSideGame(mBaseGame);
	 mClientSideNetwork = new ClientSideNetwork(mClientSideGame);
	 mClientSideNetwork->StartConnection();
		 //mBaseGame->mClientSideGame->mClientSideNetwork->StartConnection();
 //StartLogConsole();
		//game = new BaseGame;
	StartLogConsole();
 
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

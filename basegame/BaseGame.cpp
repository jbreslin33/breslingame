/*
-----------------------------------------------------------------------------
Filename:    BaseGame.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "BaseGame.h"
#include "../charactercontrollers/Character.h"
#include "CArmyWar.h"


//-------------------------------------------------------------------------------------
BaseGame::BaseGame(void)
{


}
//-------------------------------------------------------------------------------------
BaseGame::~BaseGame(void)
{
}

//-------------------------------------------------------------------------------------
void BaseGame::createScene(void)
{

	mSceneMgr->setAmbientLight(ColourValue(0.3, 0.3, 0.3));

    // add a bright light above the scene
	Light* light = mSceneMgr->createLight();
	light->setType(Light::LT_POINT);
	light->setPosition(-10, 40, 20);
	light->setSpecularColour(ColourValue::White);

	// create a floor mesh resource
	MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	Plane(Vector3::UNIT_Y, 0), 200, 200, 10, 10, true, 1, 10, 10, Vector3::UNIT_Z);

	// create a floor entity, give it a material, and place it at the origin
    Entity* floor = mSceneMgr->createEntity("Floor", "floor");
    floor->setMaterialName("Examples/Rockwall");
    floor->setCastShadows(false);
    mSceneMgr->getRootSceneNode()->attachObject(floor);

	//add a character
    //jay       = new Character(mSceneMgr, "jay"      , "Sinbad.mesh", "RunBase",  0,  5, 0);

	//mGame->myCharacter = jay;


	// Create application object
    mGame = new CArmyWar(this);
    //Ogre::LogManager::getSingletonPtr()->logMessage("*HELLO ***");
	//game = new CArmyWar;
	mGame->StartConnection(1);// doesn't matter what you pass in cause it ain't used.


	//LogManager::getSingleton().logMessage("*-*-* OGRE Initialising");

}


bool BaseGame::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
 
//#ifdef WIN32 
   if (mKeyboard->isKeyDown(OIS::KC_I)) // Forward
    {
		mGame->keys[VK_UP] = true;
		
    }
	else
	{
        mGame->keys[VK_UP] = false;
	}
    if (mKeyboard->isKeyDown(OIS::KC_K)) // Backward
    {
		mGame->keys[VK_DOWN] = true;
    }
	else
	{
        mGame->keys[VK_DOWN] = false;
	}

    if (mKeyboard->isKeyDown(OIS::KC_J)) // Left - yaw or strafe
    {
		mGame->keys[VK_LEFT] = true;
    }
	else
	{
        mGame->keys[VK_LEFT] = false;
	}
    if (mKeyboard->isKeyDown(OIS::KC_L)) // Right - yaw or strafe
    {
		mGame->keys[VK_RIGHT] = true;
    }
	else
	{
        mGame->keys[VK_RIGHT] = false;
	}
         
//#endif
    return true;
}
//-------------------------------------------------------------------------------------
bool BaseGame::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    bool ret = BaseApplication::frameRenderingQueued(evt);
 
    if(!processUnbufferedInput(evt)) return false;

	if(mGame != NULL)
	{
		mGame->RunNetwork(evt.timeSinceLastFrame * 1000);
		mGame->CheckKeys();
		mGame->Frame();
	}
 
    return ret;
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
        BaseGame app;

        try {
            app.go();
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

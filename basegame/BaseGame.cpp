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
#include "../charactercontrollers/SinbadCharacterController.h"
#include "CArmyWar.h"
#include "../../ogre/Samples/Common/include/SdkCameraMan.h"

using namespace Ogre;
using namespace OgreBites;

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

	mCameraMan->setStyle(CS_MANUAL);

        //add a character
    	//mChara = new SinbadCharacterController(getCamera(),1,1);
	//getCamera()->setPosition(100,10,0);

        // Create application object
    	mGame = new CArmyWar(this);
        mGame->StartConnection(1);// doesn't matter what you pass in cause it ain't used.

}


bool BaseGame::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
 
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
         
    	return true;
}
//-------------------------------------------------------------------------------------
bool BaseGame::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	 bool ret = BaseApplication::frameRenderingQueued(evt);

	if (mGame->localClient)
	{
		if (mGame->localClient->character)
		{	
			mGame->localClient->character->addTime(evt.timeSinceLastFrame);
		}	
	}

	//mChara->addTime(evt.timeSinceLastFrame);
    	if(!processUnbufferedInput(evt)) return false;

	if(mGame != NULL)
	{


	mGame->RunNetwork(evt.timeSinceLastFrame * 1000);
	mGame->CheckKeys();
	mGame->Frame();
	//if (mGame->clientList->character != NULL)	
	//mGame->clientList->character->addTime(evt.timeSinceLastFrame);
	}
 
    	return ret;
}


        bool BaseGame::keyPressed(const OIS::KeyEvent& evt)
        {
BaseApplication::keyPressed(evt);       
         // relay input events to character controller
                //if (!mTrayMgr->isDialogVisible()) 
//mChara->injectKeyDown(evt);
               // return SdkSample::keyPressed(evt);
        }

        bool BaseGame::keyReleased(const OIS::KeyEvent& evt)
        {
                // relay input events to character controller
                //if (!mTrayMgr->isDialogVisible()) 
//mChara->injectKeyUp(evt);
                //return SdkSample::keyReleased(evt);
        }

#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
        bool BaseGame::touchPressed(const OIS::MultiTouchEvent& evt)
        {
                // relay input events to character controller
                ///if (!mTrayMgr->isDialogVisible()) 
//mChara->injectMouseDown(evt);
                //return SdkSample::touchPressed(evt);
        }

        bool BaseGame::touchMoved(const OIS::MultiTouchEvent& evt)
        {
                // relay input events to character controller
                //if (!mTrayMgr->isDialogVisible())
 //mChara->injectMouseMove(evt);
                //return SdkSample::touchMoved(evt);
        }
#else
        bool BaseGame::mouseMoved(const OIS::MouseEvent& evt)
        {
                // relay input events to character controller
//                if (!mTrayMgr->isDialogVisible()) 
//mChara->injectMouseMove(evt);
 //               return SdkSample::mouseMoved(evt);
        }

        bool BaseGame::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
        {
                // relay input events to character controller
//                if (!mTrayMgr->isDialogVisible()) 
//mChara->injectMouseDown(evt, id);
 //               return SdkSample::mousePressed(evt, id);
        }
#endif




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

        	try
 		{
            		app.go();
        	}
			catch( Ogre::Exception& e )
		{
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

#include "baseGame.h"

#include "../client/ClientSideClient.h"
#include "../game/ClientSideGame.h"
#include "../network/clientSideNetwork.h"
#include "../shape/shape.h"

bool keys[256];

BaseGame::BaseGame()
{
	mClientSideNetwork = NULL;
	mClientSideGame    = NULL;
}

BaseGame::~BaseGame()
{

}

void BaseGame::createPlayer(int index)
{

	//create a human player and or ghost player 
	Shape jay = Shape(mSceneMgr,"jay" + index,"sinbad.mesh",0,0,0);
	mShapeVector.push_back(jay);
	
	ClientSideClient *client = mClientSideGame->GetClientPointer(index);
	client->myNode = jay.getSceneNode();
	

}

void BaseGame::createScene(void)
{
        mSceneMgr->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));

        Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
        pointLight->setType(Ogre::Light::LT_POINT);
        pointLight->setPosition(Ogre::Vector3(250, 150, 250));
        pointLight->setDiffuseColour(Ogre::ColourValue::White);
	pointLight->setSpecularColour(Ogre::ColourValue::White);
	
	// create a floor mesh resource
	MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	Plane(Vector3::UNIT_Y, 0), 100, 100, 10, 10, true, 1, 10, 10, Vector3::UNIT_Z);

	// create a floor entity, give it a material, and place it at the origin
        Entity* floor = mSceneMgr->createEntity("Floor", "floor");
        floor->setMaterialName("Examples/Rockwall");
	floor->setCastShadows(false);
        mSceneMgr->getRootSceneNode()->attachObject(floor);
}

bool BaseGame::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
//from jim: I believe having this here makes local client react faster as
//this is where ogre wants movement code. but....
//it causes a longer delay to server. needs to get to server quicker!
        mClientSideGame->inputClient.command.key = 0;
    	
	if (mKeyboard->isKeyDown(OIS::KC_I)) // Forward
    	{
		mClientSideGame->inputClient.command.key |= KEY_UP;
   	}
	
	if (mKeyboard->isKeyDown(OIS::KC_K)) // Backward
	{
	
                mClientSideGame->inputClient.command.key |= KEY_DOWN;
	}

    	if (mKeyboard->isKeyDown(OIS::KC_J)) // Left - yaw or strafe
	{

                mClientSideGame->inputClient.command.key |= KEY_LEFT;
	}

	if (mKeyboard->isKeyDown(OIS::KC_L)) // Right - yaw or strafe
	{

                mClientSideGame->inputClient.command.key |= KEY_RIGHT;
	}
      	
	mClientSideGame->inputClient.command.msec = (int) (mClientSideGame->frametime * 1000);

    return true;
}

bool BaseGame::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    bool ret = BaseApplication::frameRenderingQueued(evt);

    if(!processUnbufferedInput(evt)) return false;

	if(mClientSideNetwork != NULL)
	{
		mClientSideGame->RunNetwork(evt.timeSinceLastFrame * 1000);
		mClientSideGame->CheckKeys();
	}

    return ret;
}

bool BaseGame::keyPressed( const OIS::KeyEvent &arg )
{
	BaseApplication::keyPressed(arg);
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
	#define UNIX
    int main(int argc, char *argv[])
#endif
    {

	BaseGame*          mBaseGame;
        mBaseGame          = new BaseGame;
	mBaseGame->mClientSideGame    = new ClientSideGame(mBaseGame);
	mBaseGame->mClientSideNetwork = new ClientSideNetwork(mBaseGame);

	mBaseGame->mClientSideGame->mClientSideNetwork = mBaseGame->mClientSideNetwork;
	mBaseGame->mClientSideNetwork->mClientSideGame = mBaseGame->mClientSideGame;

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	mBaseGame->mClientSideNetwork->StartConnection(strCmdLine);
#else
	mBaseGame->mClientSideNetwork->StartConnection(argv[1]);
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

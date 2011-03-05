#include "soloGame.h"
#include "../tdreamsock/dreamSock.h"

SoloGame::SoloGame()
{

}
SoloGame::~SoloGame()
{

}

void SoloGame::createScene(void)
{
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.25, 0.25, 0.25));

    //Ogre::Entity* ninjaEntity = mSceneMgr->createEntity("Ninja", "sinbad.mesh");
    //Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("NinjaNode");
    //node->attachObject(ninjaEntity);

    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(250, 150, 250));
    pointLight->setDiffuseColour(Ogre::ColourValue::White);
    pointLight->setSpecularColour(Ogre::ColourValue::White);

	AddClient(1,1,"hello");
}

//**************************************************************
//BEGIN NETWORK CODE FUNCTIONS
//************************************************
void SoloGame::StartConnection(char* serverIP)
{

}

//-------------------------------------------------------------------------------------
 void SoloGame::go(void)
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
		CheckKeys();
		MovePlayer();
		//MoveObjects();
		Ogre::WindowEventUtilities::messagePump();
		keepRunning = mRoot->renderOneFrame();
	}

    // clean up
    destroyScene();
}

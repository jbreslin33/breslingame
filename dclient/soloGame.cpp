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

}

//**************************************************************
//BEGIN NETWORK CODE FUNCTIONS
//************************************************
void SoloGame::StartConnection(char* serverIP)
{
	AddClient(1,1,"hello");
//
}






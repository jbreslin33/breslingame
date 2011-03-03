#include "soloGame.h"

SoloGame::SoloGame()
{
}
SoloGame::~SoloGame()
{
}

void SoloGame::createScene(void)
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

//**************************************************************
//BEGIN NETWORK CODE FUNCTIONS
//************************************************
void SoloGame::StartConnection(char* serverIP)
{
	AddClient(1,1,'hello');
}
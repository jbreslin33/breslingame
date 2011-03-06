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

void PolyNetworkedGame::gameLoop()
{
	CheckKeys();
	RunNetwork(rendertime * 1000);
	Ogre::WindowEventUtilities::messagePump();
	keepRunning = mRoot->renderOneFrame();
}

void PolyNetworkedGame::AddClient(int local, int ind, char *name)
{
	Game::AddClient(local,ind,name);

	// If we just joined the game, request a non-delta compressed frame
	if(local)
		SendRequestNonDeltaFrame();
}



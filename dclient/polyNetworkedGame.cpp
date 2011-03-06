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
	Game::createScene();
}

void PolyNetworkedGame::gameLoop()
{
	CheckKeys();
	RunNetwork(rendertime * 1000);
	Ogre::WindowEventUtilities::messagePump();
	keepRunning = mRoot->renderOneFrame();
}





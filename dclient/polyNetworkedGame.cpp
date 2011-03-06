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

void PolyNetworkedGame::AddClient(int local, int ind, char *name)
{
	Game::AddClient(local,ind,name);

	// If we just joined the game, request a non-delta compressed frame
	if(local)
		SendRequestNonDeltaFrame();
}



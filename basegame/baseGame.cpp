#include "baseGame.h"

bool keys[256];

BaseGame::BaseGame()
{
	
}

BaseGame::~BaseGame()
{

}

void BaseGame::createPlayer(int index)
{
}

void BaseGame::createScene(void)
{
}

bool BaseGame::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
	return true;

}

bool BaseGame::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	return true;
}

bool BaseGame::keyPressed( const OIS::KeyEvent &arg )
{
	return true;
}

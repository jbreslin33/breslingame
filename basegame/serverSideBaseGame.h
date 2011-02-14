#ifndef SERVERSIDEBASEGAME_H
#define SERVERSIDEBASEGAME_H

//extern bool keys[256];

#include "baseGame.h"

#include <vector>

class ServerSideBaseGame : public BaseGame 
{
public:

ServerSideBaseGame();
~ServerSideBaseGame();

bool processUnbufferedInput(const Ogre::FrameEvent& evt);

void         createPlayer(int index);
virtual void createScene(void);
virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
void go(void);

};

#endif

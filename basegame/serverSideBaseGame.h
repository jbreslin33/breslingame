#ifndef SERVERSIDEBASEGAME_H
#define SERVERSIDEBASEGAME_H

#include "baseGame.h"

#include <vector>

class ServerSideGame;

class ServerSideBaseGame : public BaseGame
{
public:
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
ServerSideBaseGame(HWND hwnd);
#else
ServerSideBaseGame();
#endif

~ServerSideBaseGame();

bool processUnbufferedInput(const Ogre::FrameEvent& evt);

void         createPlayer(int index);
virtual void createScene(void);
virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
void go(void);

ServerSideGame* mServerSideGame;

};

#endif

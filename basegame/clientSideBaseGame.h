#ifndef CLIENTSIDEBASEGAME_H
#define CLIENTSIDEBASEGAME_H

#include "baseGame.h"

class ClientSideGame;

class ClientSideBaseGame : public BaseGame
{
public:

ClientSideBaseGame(const char* serverIP);
~ClientSideBaseGame();

bool processUnbufferedInput(const Ogre::FrameEvent& evt);

//void         createPlayer(int index);
virtual void createScene(void);
virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
virtual bool keyPressed( const OIS::KeyEvent &arg );

OIS::Keyboard* getKeyBoard() { return  mKeyboard; }

ClientSideGame*    mClientSideGame;

const char* mServerIP;

};

#endif

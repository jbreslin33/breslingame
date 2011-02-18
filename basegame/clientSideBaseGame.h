#ifndef CLIENTSIDEBASEGAME_H
#define CLIENTSIDEBASEGAME_H

#include "baseGame.h"

#include <vector>

class ClientSideGame;
class ClientSideShape;

class ClientSideBaseGame : public BaseGame
{
public:

ClientSideBaseGame(const char* serverIP);
~ClientSideBaseGame();

bool processUnbufferedInput(const Ogre::FrameEvent& evt);

void         createPlayer(int index);
virtual void createScene(void);
virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
virtual bool keyPressed( const OIS::KeyEvent &arg );

OIS::Keyboard* getKeyBoard() { return  mKeyboard; }

ClientSideGame*    mClientSideGame;

std::vector<ClientSideShape*> mShapeVector;

const char* mServerIP;

};

#endif

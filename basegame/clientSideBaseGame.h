#ifndef CLIENTSIDEBASEGAME_H
#define CLIENTSIDEBASEGAME_H

//extern bool keys[256];

#include "baseGame.h"

#include <vector>

class ClientSideNetwork;
class ClientSideGame;
class ClientSideShape;

class ClientSideBaseGame : public BaseGame
{
public:

ClientSideBaseGame();
~ClientSideBaseGame();

bool processUnbufferedInput(const Ogre::FrameEvent& evt);

void         createPlayer(int index);
virtual void createScene(void);
virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
virtual bool keyPressed( const OIS::KeyEvent &arg );

OIS::Keyboard* getKeyboard() { return  mKeyboard; }

ClientSideNetwork* mClientSideNetwork;
ClientSideGame*    mClientSideGame;

std::vector<ClientSideShape*> mShapeVector;

};

#endif

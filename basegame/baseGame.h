#ifndef BASEGAME_H
#define BASEGAME_H

extern bool keys[256];

#include "../baseapplication/BaseApplication.h"

#include <vector>

class ClientSideNetwork;
class ClientSideGame;
class ClientSideShape;

class BaseGame : public BaseApplication
{
public:

BaseGame();
~BaseGame();

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

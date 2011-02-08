#ifndef BASEGAME_H
#define BASEGAME_H

extern bool keys[256];

#include "../baseapplication/BaseApplication.h"

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

};

#endif

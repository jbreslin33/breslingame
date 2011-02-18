#ifndef BASEGAME_H
#define BASEGAME_H

extern bool keys[256];

#include "../baseapplication/baseApplication.h"

class BaseGame : public BaseApplication
{
public:

BaseGame();
~BaseGame();

virtual void createScene(void);
virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
virtual bool keyPressed( const OIS::KeyEvent &arg );

OIS::Keyboard* 	    getKeyboard    () { return mKeyboard; }
Ogre::SceneManager* getSceneManager() { return mSceneMgr; }

};

#endif

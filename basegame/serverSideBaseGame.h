#ifndef SERVERSIDEBASEGAME_H
#define SERVERSIDEBASEGAME_H

extern bool keys[256];

#include "../baseapplication/BaseApplication.h"

#include <vector>

class ServerSideShape;

class ServerSideBaseGame : public BaseApplication
{
public:

ServerSideBaseGame();
~ServerSideBaseGame();

bool processUnbufferedInput(const Ogre::FrameEvent& evt);

void         createPlayer(int index);
virtual void createScene(void);
virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
//virtual bool keyPressed( const OIS::KeyEvent &arg );

//OIS::Keyboard* getKeyboard() { return  mKeyboard; }


//std::vector<ServerSideShape*> mShapeVector;


};

#endif

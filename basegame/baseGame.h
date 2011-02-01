#ifndef BASEGAME_H
#define BASEGAME_H

#include "../baseapplication/BaseApplication.h"


#ifdef WIN32
        //do nothing
#else

#define VK_ESCAPE 0     
#define VK_DOWN 1
#define VK_UP 2
#define VK_LEFT 3
#define VK_RIGHT 4
#define VK_SPACE 5
#endif

class ClientSideGame;

// The main application class interface
class BaseGame : public BaseApplication
{
private:

public:
	BaseGame();
	~BaseGame();

void createPlayer(int index);
bool         processUnbufferedInput(const Ogre::FrameEvent& evt);
virtual void createScene(void);
virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
virtual bool keyPressed( const OIS::KeyEvent &arg );

ClientSideGame* mClientSideGame;

bool keys[256];
};

#endif

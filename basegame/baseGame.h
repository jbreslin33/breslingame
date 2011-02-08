#ifndef BASEGAME_H
#define BASEGAME_H

#include "../baseapplication/BaseApplication.h"
#include "../command/ClientSideCommand.h"
#include "../client/ClientSideClient.h"
#include "../math/Vector3D.h"

#include "../network/clientSideNetwork.h"

//class DreamMessage;
//class DreamClient;

extern bool keys[256];

//keys for linux
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

// The main application class interface
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

	// Client.cpp

};

#endif

/*
-----------------------------------------------------------------------------
Filename:    BaseGame.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __BaseGame_h_
#define __BaseGame_h_

#include "../baseapplication/BaseApplication.h"

class CArmyWar;
class SinbadCharacterController;
class Character;
class BaseGame : public BaseApplication
{
public:
	BaseGame(void);
    	virtual ~BaseGame(void);

bool processUnbufferedInput(const Ogre::FrameEvent& evt);
bool frameRenderingQueued  (const Ogre::FrameEvent& evt);
bool keyPressed(const OIS::KeyEvent&);
bool keyReleased(const OIS::KeyEvent&);
bool mouseMoved(const OIS::MouseEvent&);
bool mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);


Ogre::SceneManager* getSceneManager()
{
	return mSceneMgr;
}

	CArmyWar*   mGame;

protected:
	virtual void createScene(void);
SinbadCharacterController* mChara;
};

#endif // #ifndef __BaseGame_h_

/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
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
#ifndef __BASEGAMEAPPLICATION
#define __BASEGAMEAPPLICATION_h_

#include "Ogre.h"

#include "../baseapplication/BaseApplication.h"

using namespace Ogre;

class MathInput;
class AdditionFactory;
class Character;

class BaseGameApplication : public BaseApplication
{
public:
        BaseGameApplication(void);
        virtual ~BaseGameApplication(void);

        void createFrameListener(void);

        OgreBites::ParamsPanel* getScoreDetailsPanel() { return mScoreDetailsPanel; }

        bool getGameStarted() { return mGameStarted; }
        void startGame    ();
        void processAnswer();

        void keyNumberHit (std::string number);

        //get objects
        AdditionFactory* getAdditionFactory() { return mAdditionFactory; }

	void breslinHideAllWidgets(void);

protected:
        virtual void createScene(void);

        // Ogre::FrameListener
        virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

        // OIS::KeyListener
        virtual bool keyPressed  (const OIS::KeyEvent &arg );
        virtual bool keyReleased (const OIS::KeyEvent &arg );

        // OIS::MouseListener
        virtual bool mouseMoved  (const OIS::MouseEvent &arg );
        virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id );
        virtual void buttonHit(OgreBites::Button* b);

        bool mGameStarted;

        OgreBites::ParamsPanel* mScoreDetailsPanel;     // sample details panel
        OgreBites::ParamsPanel* mSignUpParamsPanel;
        
        OgreBites::Button*      mSignUpButton;
        OgreBites::Button*      mSignInButton;
        OgreBites::Button*      mQuitButton;
        
        AdditionFactory* mAdditionFactory;
        MathInput*       mMathInput;

        Character*    jay;
        Character*    silentbob;

};

#endif // #ifndef __TutorialApplication_h_



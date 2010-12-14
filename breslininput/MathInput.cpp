
#include "MathInput.h"
#include "../basegameapplication/BaseGameApplication.h"
#include "../questionfactory/AdditionFactory.h"

#include "Ogre.h"

MathInput::MathInput(BaseGameApplication* mathRacer)
{
    mBaseGameApplication    = mathRacer;
}

MathInput::~MathInput()
{
}

// a number is hit what should happen? append to var in question factory and display on screen....
void MathInput::keyNumberHit(const OIS::KeyEvent &arg)
{
    std::string number   = Ogre::StringConverter::toString(arg.key -1);

    //this should update variable
    mBaseGameApplication->getAdditionFactory()->keyNumberHit(number);

    //this should update display
    mBaseGameApplication->keyNumberHit(number);

}

void MathInput::injectKeyDown(const OIS::KeyEvent& evt)
{
    if (evt.key == OIS::KC_M)
    {
        mBaseGameApplication->startGame();
    }
    else if (evt.key == OIS::KC_0)
    {
        keyNumberHit(evt);
    }
    else if (evt.key == OIS::KC_1)
    {
        keyNumberHit(evt);
    }
    else if (evt.key == OIS::KC_2)
    {
        keyNumberHit(evt);
    }
    else if (evt.key == OIS::KC_3)
    {
        keyNumberHit(evt);
    }
    else if (evt.key == OIS::KC_4)
    {
        keyNumberHit(evt);
    }
    else if (evt.key == OIS::KC_5)
    {
        keyNumberHit(evt);
    }
    else if (evt.key == OIS::KC_6)
    {
        keyNumberHit(evt);
    }
    else if (evt.key == OIS::KC_7)
    {
        keyNumberHit(evt);
    }
    else if (evt.key == OIS::KC_8)
    {
        keyNumberHit(evt);
    }
    else if (evt.key == OIS::KC_9)
    {
        keyNumberHit(evt);
    }
    else if (evt.key == OIS::KC_RETURN)
    {
        mBaseGameApplication->processAnswer();
    }
}

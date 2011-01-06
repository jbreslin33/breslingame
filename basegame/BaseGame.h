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

class BaseGame : public BaseApplication
{
public:
    BaseGame(void);
    virtual ~BaseGame(void);

protected:
    virtual void createScene(void);
};

#endif // #ifndef __BaseGame_h_

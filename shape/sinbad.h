#ifndef SINBAD_H
#define SINBAD_H

#include "clientSideShape.h"

#include "Ogre.h"
#include "OIS.h"

using namespace Ogre;

class Sinbad : public ClientSideShape
{

public:

Sinbad(Ogre::SceneManager* mSceneMgr, std::string name, int xPos, int yPos, int zPos, std::string mesh); 
~Sinbad();

virtual void updateAnimations(Real renderTime);
virtual void setupAnimations();

};

#endif


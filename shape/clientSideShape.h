#ifndef CLIENTSIDESHAPE_H
#define CLIENTSIDESHAPE_H

#include "shape.h"

#include "Ogre.h"
#include "OIS.h"

using namespace Ogre;

class ClientSideShape : public Shape
{

public:

ClientSideShape(Ogre::SceneManager* mSceneMgr, std::string name, int xPos, int yPos, int zPos, std::string mesh); 
~ClientSideShape();


void setupModel();
void updatePosition(Real deltaTime);
virtual void updateAnimations(Real renderTime);
virtual void setupAnimations() { bool donothing; }

//stats
std::string mMeshName;

Entity* mEntity;

Vector3 mKeyDirection;      // player's local intended direction based on WASD keys
Vector3 mGoalDirection;
AnimationState *mAnimationState;
};

#endif


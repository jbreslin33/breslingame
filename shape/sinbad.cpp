#include "sinbad.h"

Sinbad::Sinbad(Ogre::SceneManager* sceneMgr, std::string shapeName,int x, int y, int z,std::string meshName) : ClientSideShape(sceneMgr,shapeName,x,y,z,meshName)
{

}

Sinbad::~Sinbad()
{
}

void Sinbad::setupAnimations()
{
	mEntity->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);
	mAnimationState = mEntity->getAnimationState("RunBase");
    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);
}

void Sinbad::updateAnimations(Real rendertime)
{
	mAnimationState = mEntity->getAnimationState("RunBase");
	mAnimationState->setLoop(true);
	mAnimationState->setEnabled(true);

	mAnimationState->addTime(rendertime);
}


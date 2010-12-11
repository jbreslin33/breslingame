#ifndef Character_H
#define Character_H


#include "Ogre.h"
#include "OIS.h"

using namespace Ogre;
//using namespace OgreBites;

class Character
{
public:

	Character(Ogre::SceneManager* mSceneMgr, std::string name, std::string mesh, std::string animation, int xPos, int yPos, int zPos); // : NUM_MODELS(6), ANIM_CHOP(8)
	~Character();

    void addTime         (Real deltaTime);
    void updateBody      (Real deltaTime);
    void updateAnimations(Real deltaTime);
    void updateCamera    (Real deltaTime);


protected:

	void setupModel();
	void cleanupContent();



    //objects
    Ogre::SceneManager* mSceneManager;
	SceneNode* mModelNodes;

    //Animation
	AnimationState* mAnimStates;
	Real mAnimSpeeds;

    //stats
    std::string mName;
    std::string mMesh;
    std::string mAnimation;
    int xPos;
    int yPos;
    int zPos;
};

#endif


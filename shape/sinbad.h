#ifndef SINBAD_H
#define SINBAD_H

#define NUM_ANIMS 13           // number of animations the character has
#define CHAR_HEIGHT 5          // height of character's center of mass above ground
#define CAM_HEIGHT 2           // height of camera above character's center of mass
#define RUN_SPEED 17           // character running speed in units per second
#define TURN_SPEED 500.0f      // character turning in degrees per second
#define ANIM_FADE_SPEED 7.5f   // animation crossfade speed in % of full weight per second
#define JUMP_ACCEL 30.0f       // character jump acceleration in upward units per squared second
#define GRAVITY 90.0f          // gravity in downward units per squared second

#include "clientSideShape.h"

#include "Ogre.h"
#include "OIS.h"

using namespace Ogre;

	// all the animations our character has, and a null ID
	// some of these affect separate body parts and will be blended together
	enum AnimID
	{
		ANIM_IDLE_BASE,
		ANIM_IDLE_TOP,
		ANIM_RUN_BASE,
		ANIM_RUN_TOP,
		ANIM_HANDS_CLOSED,
		ANIM_HANDS_RELAXED,
		ANIM_DRAW_SWORDS,
		ANIM_SLICE_VERTICAL,
		ANIM_SLICE_HORIZONTAL,
		ANIM_DANCE,
		ANIM_JUMP_START,
		ANIM_JUMP_LOOP,
		ANIM_JUMP_END,
		ANIM_NONE
	};

class Sinbad : public ClientSideShape
{

public:

Sinbad(Ogre::SceneManager* mSceneMgr, std::string name, int xPos, int yPos, int zPos, std::string mesh); 
~Sinbad();

virtual void updateAnimations(Real renderTime);
void updateBody(Real deltaTime);
virtual void setupAnimations();
void fadeAnimations(Real deltaTime);
void setTopAnimation(AnimID id, bool reset);
void setBaseAnimation(AnimID id, bool reset);
virtual void addTime(Real deltaTime);
virtual void injectKeyDown(const OIS::KeyEvent& evt);
virtual void injectKeyUp(const OIS::KeyEvent& evt);
virtual void setupModel();


	Entity* mSword1;
	Entity* mSword2;
	RibbonTrail* mSwordTrail;
	AnimationState* mAnims[NUM_ANIMS];    // master animation list
	AnimID mBaseAnimID;                   // current base (full- or lower-body) animation
	AnimID mTopAnimID;                    // current top (upper-body) animation
	bool mFadingIn[NUM_ANIMS];            // which animations are fading in
	bool mFadingOut[NUM_ANIMS];           // which animations are fading out
	bool mSwordsDrawn;
	Real mTimer;                // general timer to see how long animations have been playing
	Real mVerticalVelocity;     // for jumping
	Vector3 mKeyDirection;      // player's local intended direction based on WASD keys
};

#endif


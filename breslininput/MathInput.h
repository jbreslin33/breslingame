#ifndef MATHINPUT_H_
#define MATHINPUT_H_

#include "OIS.h"

class BaseGameApplication;

class MathInput
{
public:
	MathInput(BaseGameApplication* mathRacer);
	~MathInput();

	void injectKeyDown(const OIS::KeyEvent& evt);
    void keyNumberHit (const OIS::KeyEvent &arg);

protected:
    BaseGameApplication* mBaseGameApplication;

};

#endif

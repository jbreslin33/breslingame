/*
-----------------------------------------------------------------------------
Basic Login class

Prompt user to login....use virtual functions so that it may exetended to use a gui....

entrys would be sent across network using usual suspects of Talker and ListenServer and MessageHandler

Filename:    Login.h
*/
#ifndef __Login_h_
#define __Login_h_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

class Game;

class Login
{

public:
	Login(Game* game);
    	virtual ~Login(void);

	virtual void promptServerIP();
	
	virtual void promptSignUpOrLogin();	
	
	virtual void promptSignUp();	
	
	virtual void promptLogin();	
	
	virtual void promptUserName();
	virtual void promptPassword();


protected:
Game* mGame;


};

#endif


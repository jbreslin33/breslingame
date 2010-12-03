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
#include <iostream>

class ClientGame;

class Login
{

public:
	Login(ClientGame* game);
    	virtual ~Login(void);

	virtual void promptServerIP();
	
	virtual void promptSignUpOrLogin();	
	
	virtual void promptSignUp();	
	virtual void signUp(char userName[100]);

	virtual void promptLogin();	
	
	virtual void promptUserName();
	virtual void promptPassword();


protected:

ClientGame* mGame;
char  mTempUserName[100];
char  mTempPassword[100];

};

#endif


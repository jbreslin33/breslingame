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


class Login
{

public:
	Login();
    	virtual ~Login(void);

	virtual void promptUserName();
	virtual void promptPassword();

protected:



};

#endif


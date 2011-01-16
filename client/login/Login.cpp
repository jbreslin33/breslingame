/*
-----------------------------------------------------------------------------
Filename:    Login.cpp
*/

#include "Login.h"
#include "../../client/ClientGame.h"
#include "../../connection/ServerConnection.h"
#include "../../communication/Communication.h"
#include <iostream>

//-------------------------------------------------------------------------------------
Login::Login(ClientGame* game)
{
	mGame = game;
	promptServerIP();

}
//-------------------------------------------------------------------------------------
Login::~Login(void)
{

}

void Login::promptServerIP()
{
        //let's get an ip for server
        std::cout << "Press Corresponding Number to Pick IP Address of Server:\n";

        std::cout << "1 = Enter one not on list\n";
        std::string one = "1";

        std::cout << "2 = 192.168.2.3 \n";
        std::string two = "2";

        std::cout << "3 = 10.42.43.1\n";
        std::string three = "3";

        std::cout << "4 = 71.23.229.73\n";
        std::string four = "4";

        //get user response save to string
        std::string str;
        getline (std::cin,str);

        if (one.compare(str) == 0)
        {
        	std::cout << "Enter IP Address of Server \n";
                char ip[16];
                std::cin.getline(ip,16);
		mGame->getServerConnection()->setIP(ip);
        }
        else if (two.compare(str) == 0)
        {
                char ip[16] = "192.168.2.3";
		mGame->getServerConnection()->setIP(ip);
        }
        else if (three.compare(str) == 0)
        {
                char ip[16] = "10.42.43.1";
		mGame->getServerConnection()->setIP(ip);
        }
        else if (four.compare(str) == 0)
        {
                char ip[16] = "71.23.229.73";
		mGame->getServerConnection()->setIP(ip);
        }
	promptSignUpOrLogin();	
}



void Login::promptSignUpOrLogin()
{
	std::cout << "Choose:\n";
	
	std::cout << "1 = Sign Up\n";
	std::string one = "1";

	std::cout << "2 = Login\n";
	std::string two = "2";

	std::cout << "3 = Quit\n";
	std::string three = "3";

        //get user response save to string
        std::string str;
        getline (std::cin,str);

	if (one.compare(str) == 0)
	{
		promptSignUp();
	}
	else if (two.compare(str) == 0)
	{
		promptLogin();
	}
	else if (three.compare(str) == 0)
	{
		exit(1);
	}
}

void Login::promptSignUp()
{
	std::cout << "in promptSignUP going to call promptUserName\n";
	promptUserName();
	std::cout << "in promptSignUP dud\n";
	signUp(mTempUserName);
}

void Login::signUp(char* userName)
{
	std::cout << "in signUP function right now\n";
	mGame->getCommunication()->send(mGame->getServerConnection(), "signUp", userName );
}

void Login::changeUserName(char* userName)
{
	std::cout << "in changeUserName\n";
	mGame->getCommunication()->send(mGame->getServerConnection(), "changeUserName", userName, mGame->convertIntToCharStar(mGame->getClientConnectionID() ));
}

void Login::promptLogin()
{
	promptUserName();
	promptPassword();
}

void Login::promptUserName()
{
	for (int i = 0; i < 30; i++)
		mTempUserName[i] = NULL;
	std::cout << "Enter your User Name: ";
  	std::cin.getline (mTempUserName,30);
}

void Login::promptPassword()
{
	std::cout << "Enter Password:\n";
        
	//get user response save to string
        std::cin.getline (mTempPassword,100);

}

void Login::enterNewUserName()
{
	promptUserName();
	changeUserName(mTempUserName);	
}

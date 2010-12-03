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
                mGame->setServerIP(ip);
		ServerConnection* sconn = new ServerConnection(ip);
		mGame->setServerConnection(sconn);
        }
        else if (two.compare(str) == 0)
        {
                char ip[16] = "192.168.2.3";
                mGame->setServerIP(ip);
		ServerConnection* sconn = new ServerConnection(ip);
		mGame->setServerConnection(sconn);
        }
        else if (three.compare(str) == 0)
        {
                char ip[16] = "10.42.43.1";
                mGame->setServerIP(ip);
		ServerConnection* sconn = new ServerConnection(ip);
		mGame->setServerConnection(sconn);
        }
        else if (four.compare(str) == 0)
        {
                char ip[16] = "71.23.229.73";
                mGame->setServerIP(ip);
		ServerConnection* sconn = new ServerConnection(ip);
		mGame->setServerConnection(sconn);
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
	std::cout << "in promptSignUP going to call promptUserName";
	promptUserName();
	std::cout << "in promptSignUP dud";
	signUp(mTempUserName);
}

void Login::signUp(char userName[100])
{
	
//	mGame->getMessageHandler()->translateMessage("toServer","signUp",userName);
	//mGame->getMessageHandler()->sendMessage("toServer,signUp,%s",userName);
//need a server connection then pass it in Connection* serverConnection = new ServerConnection(A
	std::cout << "in signUP function right now";
	std::vector<std::string> message;
	message.push_back("signUp");	
	message.push_back(userName);

	mGame->getCommunication()->send(mGame->getServerConnection(), message);
}

void Login::promptLogin()
{
	promptUserName();
	promptPassword();
}

void Login::promptUserName()
{
//	std::cout << "Enter UserName:\n";
        
	//get user response save to string
  //      std::cin.getline (mTempUserName,100);


        //get user response save to string
        std::string str;
        getline (std::cin,str);




}

void Login::promptPassword()
{
	std::cout << "Enter Password:\n";
        
	//get user response save to string
        std::cin.getline (mTempPassword,100);

}



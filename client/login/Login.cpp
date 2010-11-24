/*
-----------------------------------------------------------------------------
Filename:    Login.cpp
*/

#include "Login.h"
//#include "messagehandler/MessageHandler.h"

//-------------------------------------------------------------------------------------
Login::Login()
{
	mMessageHandler = new MessageHandler();
}
//-------------------------------------------------------------------------------------
Login::~Login(void)
{
}

void Login::promptSignUpOrLogin()
{

	Login* login = new Login();	

	std::cout << "Choose:\n";
	
	std::cout << "1 = Sign Up\n";
	std::string one = "1";

	std::cout << "2 = Login\n";
	std::string two = "2";

	std::cout << "3 = Quit\n";
	std::string two = "3";

	
        //get user response save to string
        std::string str;
        getline (std::cin,str);


	if (one.compare(str) == 0)
	{
		//std::cout << "Launch SignUp Prompt\n";
		//login->promptSignUp();
	}
	else if (two.compare(str) == 0)
	{
		login->promptLogin();
	}
	else if (three.compare(str) == 0)
	{
		exit(i);
	}
}

void Login::promptUserName()
{
/*
	std::cout << "UserName:\n";

	std::cout << "Enter UserName:\n";
		char ip[16];
		std::cin.getline(ip,16);	
*/
}

void Login::promptPassword()
{

}


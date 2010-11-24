#include "Game.h"
#include <iostream>
#include <string>

#include "talker/Talker.h"
#include "messagehandler/MessageHandler.h"
#include "listenserver/ListenServer.h"
#include "client/questiongame/QuestionClientGame.h"
#include "server/questiongame/QuestionServerGame.h"


int main(int argc, char *argv[])
{


	std::cout << "Press Corresponding Number to Launch:\n";
	
	std::cout << "1 = QuestionServerGame\n";
	std::string one = "1";

	std::cout << "2 = Talker\n";
	std::string two = "2";

	std::cout << "3 = QuestionClientGame\n";
	std::string three = "3";
	
        //get user response save to string
        std::string str;
        getline (std::cin,str);


	if (one.compare(str) == 0)
	{
		std::cout << "Launch A QuestionServerGame\n";
		QuestionServerGame* game = new QuestionServerGame();
	}
	else if (two.compare(str) == 0)
	{
		std::cout << "Launch Talker\n";

       	 	//get user response save to string

		std::cout << "Enter IP Address of Server\n";
		char ip[16];
		std::cin.getline(ip,16);
	
		Talker* talker = new Talker();
		talker->setServerIP(ip);
	
	}

	else if (three.compare(str) == 0)
	{
		std::cout << "Launch QuestionClientGame\n";
		QuestionClientGame* game = new QuestionClientGame();
		
	        //let's get an ip for server
		std::cout << "Press Corresponding Number to Pick IP Address of Server:\n";

		std::cout << "1 = Enter one not on list\n";
		std::string one = "1";
	
        	std::cout << "2 = 192.168.2.3 \n";
        	std::string two = "2";

        	std::cout << "3 = 10.42.43.1\n";
        	std::string three = "3";

        	//get user response save to string
        	std::string str;
        	getline (std::cin,str);

		if (one.compare(str) == 0)
		{
			std::cout << "Enter IP Address of Server \n";
			char ip[16];
			std::cin.getline(ip,16);

			game->getMessageHandler()->getTalker()->setServerIP(ip);
		}
		else if (two.compare(str) == 0)
		{
			//std::string ip = "192.168.2.3";
			char ip[16] = "192.168.2.3";
			game->getMessageHandler()->getTalker()->setServerIP(ip);
		}
		else if (three.compare(str) == 0)
		{
			char ip[16] = "10.42.43.1";
			game->getMessageHandler()->getTalker()->setServerIP(ip);
		}
		
		//okay you have an ip address now ask if they want to login do this with a class....	

	}

	else
	{
		std::cout << "I don't know what you want so I am doing nothing!\n";
	}

}


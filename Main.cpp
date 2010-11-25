#include "Game.h"
#include <iostream>
#include <string>

#include "client/questiongame/QuestionClientGame.h"
#include "server/questiongame/QuestionServerGame.h"


int main(int argc, char *argv[])
{


	std::cout << "Press Corresponding Number to Launch:\n";
	
	std::cout << "1 = QuestionServerGame\n";
	std::string one = "1";

	std::cout << "2 = QuestionClientGame\n";
	std::string two = "2";
	
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
		std::cout << "Launch QuestionClientGame\n";
		QuestionClientGame* game = new QuestionClientGame();
	}

	else
	{
		std::cout << "I don't know what you want so I am doing nothing!\n";
	}

}


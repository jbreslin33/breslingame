#include "Game.h"
#include <iostream>
#include <string>

#include "server/questiongame/QuestionServerGame.h"
#include "talker/Talker.h"


int main(int argc, char *argv[])
{

	std::string questionGameServer = "QuestionServerGame";
	std::string talker             = "Talker";


	if (questionGameServer.compare(argv[1]) == 0)
	{
		std::cout << "Launch A QuestionServerGame\n";
		QuestionServerGame* game = new QuestionServerGame();
	}
	else if (talker.compare(argv[1]) == 0)
	{
		std::cout << "Launch Talker\n";
		Talker* talker = new Talker();
	}

	else
	{
		std::cout << "I don't know what you want so I am doing nothing!\n";
	}

}

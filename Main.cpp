#include "Game.h"
#include <iostream>
#include <string>

#include "server/questiongame/QuestionServerGame.h"

int main(int argc, char *argv[])
{

	std::string qgs = "QuestionServerGame";

	if (qgs.compare(argv[1]) == 0)
	{
		std::cout << "Launch A QuestionServerGame\n";
		QuestionServerGame* game = new QuestionServerGame();
	}
	else
	{
		std::cout << "I don't know what you want so I am doing nothing!\n";
	}

}

#include "QuestionFactory.h"

#include <stdlib.h>
#include <sstream>
#include <iostream>

QuestionFactory::QuestionFactory()
{
    mQuestion = "What is the meaning of Life the Universe and Everything?";
    mCorrectAnswer = "";
    mPlayerAnswer = "";
}

QuestionFactory::~QuestionFactory()
{
}

bool QuestionFactory::checkAnswer()
{
	if (mCorrectAnswer == mPlayerAnswer)
	{
	    resetVariables();
		return true;
	}
	else
	{
	    resetVariables();
		return false;
	}
}

void QuestionFactory::resetVariables()
{
    mPlayerAnswer  = "";
    mCorrectAnswer = "";
    mQuestion      = "";
}


void QuestionFactory::keyNumberHit(std::string number)
{
    mPlayerAnswer.append(number);
}

std::string QuestionFactory::convertInt(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}






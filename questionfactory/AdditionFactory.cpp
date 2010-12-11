#include "AdditionFactory.h"

#include <stdlib.h>
#include <sstream>
#include <iostream>

AdditionFactory::AdditionFactory()
{
}

AdditionFactory::~AdditionFactory()
{
}

std::string AdditionFactory::getQuestion()
{
   srand ( time(NULL) );

   /* generate numbers: */
   int number1 = rand() % 10 + 1;
   int number2 = rand() % 10 + 1;
   int correctAnswerInt = number1 + number2;

   mCorrectAnswer = convertInt(correctAnswerInt);

   mQuestion = convertInt(number1) + " + " + convertInt(number2) + " = ";

   return mQuestion;
}



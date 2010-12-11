#include "SubtractionFactory.h"

#include <stdlib.h>
#include <sstream>
#include <iostream>

SubtractionFactory::SubtractionFactory()
{
}

SubtractionFactory::~SubtractionFactory()
{
}

std::string SubtractionFactory::getQuestion()
{
   srand ( time(NULL) );

   /* generate numbers: */
   int number1 = rand() % 10 + 1;
   int number2 = rand() % 10 + 1;
   int correctAnswer = number1 - number2;

   mCorrectAnswer = convertInt(correctAnswer);

   mQuestion = convertInt(number1) + " - " + convertInt(number2) + " = ";

   return mQuestion;
}



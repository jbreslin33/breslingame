#include "QuestionGenreSwitcher.h"
#include "AdditionFactory.h"
#include "SubtractionFactory.h"
#include <iostream>
#include <stdlib.h>

QuestionGenreSwitcher::QuestionGenreSwitcher()
{
    additionFactory    = new AdditionFactory   ();
    subtractionFactory = new SubtractionFactory();

    factoryVector.push_back(additionFactory);
    factoryVector.push_back(subtractionFactory);
}

QuestionGenreSwitcher::~QuestionGenreSwitcher()
{
}

QuestionFactory* QuestionGenreSwitcher::getFactory()
{
    return additionFactory;
}

QuestionFactory* QuestionGenreSwitcher::getRandomFactory()
{
    srand ( time(NULL) );
    int element = rand() % 2 + 0;
    return factoryVector[element];
}

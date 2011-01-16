#ifndef QUESTIONGENRESWITCHER_H_
#define QUESTIONGENRESWITCHER_H_

#include <vector>
#include <string>

#include "QuestionFactory.h"

//class QuestionFactory;
class AdditionFactory;
class SubtractionFactory;


class QuestionGenreSwitcher
{
public:
	QuestionGenreSwitcher();
	~QuestionGenreSwitcher();

QuestionFactory* getFactory();
QuestionFactory* getRandomFactory();

AdditionFactory*    additionFactory;
SubtractionFactory* subtractionFactory;

std::vector <QuestionFactory*> factoryVector;

};

#endif
